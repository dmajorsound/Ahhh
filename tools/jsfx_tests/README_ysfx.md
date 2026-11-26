# roomservice – Testwerkzeuge und ysfx-Host

Alles, was ich benutze, um das Plugin zu prüfen, ohne es in REAPER zu laden. Der Host ist **ysfx** von jpcima – dieselbe JSFX-Engine wie in REAPER, als Bibliothek. Dazu ein kleines eigenes Hostprogramm (`render.cpp` → `render0`), das das Plugin kompiliert, Audioblöcke durchlaufen lässt, `@gfx` mit geskripteter Mauseingabe aufruft und Frames als PPM speichert.

**Wichtig und ehrlich:** Das ist ein Linux-Host. Er prüft Kompilierbarkeit, Zahlen, Zustände und das GUI-Bild. Er sagt nichts darüber, wie es in REAPER klingt oder aussieht. In meinen Berichten steht deshalb immer dazu, dass nichts in REAPER gehört wurde.

---

## 1 · Host bauen

ysfx holen und bauen (einmalig). Getestet mit Commit `8077347`:

```sh
git clone https://github.com/jpcima/ysfx.git
cd ysfx
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j8          # ergibt build/libysfx.a
```

Dann das Hostprogramm dagegen bauen (`render.cpp` liegt in diesem Paket):

```sh
g++ -O2 -std=c++17 render.cpp -o render0 \
    -I/PFAD/ZU/ysfx/include -L/PFAD/ZU/ysfx/build -lysfx \
    -ldl -lpthread
```

Auf macOS statt `-ldl -lpthread`:

```sh
g++ -O2 -std=c++17 render.cpp -o render0 \
    -I/PFAD/ZU/ysfx/include -L/PFAD/ZU/ysfx/build -lysfx \
    -framework Cocoa -framework Foundation
```

`render0` muss im selben Ordner liegen wie die Skripte. Python braucht nur `pillow` und `numpy`:

```sh
pip3 install pillow numpy
```

---

## 2 · Wie `render0` aufgerufen wird

```
./render0 datei.jsfx BREITE HOEHE skriptdatei
```

Die Skriptdatei enthält eine Anweisung pro Zeile:

**Bild und Eingabe**

| Zeile | Wirkung |
|---|---|
| `frame [N]` | N `@gfx`-Durchläufe (Default 1) |
| `mouse X Y BTN MODS` | Mausposition und -tasten (BTN 1 = links; MODS 1 = Shift, 2 = Ctrl, 4 = Alt) |
| `wheel W` | Mausrad, Wert relativ |
| `key CODE` / `keys TEXT` | Tastendruck bzw. eine Folge von Zeichen |
| `save datei.ppm` | aktuellen Frame als PPM speichern |

**Audio**

| Zeile | Wirkung |
|---|---|
| `audio N AMP` | N Blöcke à 256 Samples Rauschen, Ausgang wird verworfen |
| `noise N AMP datei` | N Blöcke gefärbtes Rauschen, Ausgang als Raw-Float nach *datei* |
| `sine N F AMP datei` | Sinus mit F Hz |
| `clicks N PERIODE AMP datei` | Impulse – für Echogramme und Nachhallmessung |
| `rawin N ein aus` | eigene Raw-Float-Datei durchschicken |
| `bsize N` | Blockgröße setzen (Default 256) |
| `srate R` | Samplerate setzen, ruft `@init` neu auf |
| `play ZUSTAND POS` | Transport simulieren (1 = läuft), Tempo 120 |

**Zustand und Variablen**

| Zeile | Wirkung |
|---|---|
| `slider N V` | Slider setzen – **0-basiert**, `slider 1 9` ist also `slider2` |
| `getslider N` | Sliderwert ausgeben |
| `var NAME WERT` | EEL-Variable schreiben |
| `print NAME` | EEL-Variable ausgeben |
| `vmem NAME ADR N` | N Speicherzellen ab `NAME + ADR` ausgeben |
| `savestate` / `loadstate` | Zustand merken und zurückladen (`@serialize` prüfen) |
| `writestate datei` / `readstate datei` | Zustand auf Platte, für Versionsvergleiche |

**Messung**

| Zeile | Wirkung |
|---|---|
| `timeaudio N` | ms pro Block, mit Budget |
| `timeframes N` | ms pro GUI-Frame |
| `blkmax N BS` | CPU bei bewegter Quelle für eine Blockgröße |
| `maxms` | Spitzenwert seit dem letzten Aufruf |

In der Praxis rufe ich das nie direkt auf, sondern über `shot.py`:

```sh
SRC=/pfad/roomservice.jsfx python3 shot.py name 1500 1080 \
  "var tb_dark 1;var tb_set 1;var tb_basic 0;var tb_vi 46;var tb_vv 7;frame;frame"
```

`shot.py` kopiert die Quelle über `mkv.sh` nach `t.jsfx` (ersetzt dabei das zweiargumentige `slider_automate`, das ysfx nicht kennt), baut Testhaken für Theme, Tab und Preset ein, rendert und speichert `name.png`.

`shot.py` hängt selbst ein `save name.ppm` ans Ende des Skripts – zwei Aufrufe mit demselben Namen überschreiben sich also gegenseitig. Für Vergleiche verschiedene Namen verwenden. (Darauf bin ich schon einmal hereingefallen und hielt einen Zeichenfehler für einen Bug.)

---

## 3 · Die Prüfungen

### Vor jeder Lieferung, Pflicht

```sh
python3 uxcheck.py roomservice.jsfx          # → UXCOUNT 0
python3 suite/runall.py NEU.jsfx VORHERIGE.jsfx
```

`uxcheck.py` rendert 22 Ansichten (Basic, Expert Tabs, All, Fit, die Zoomstufen) in 9 Fenstergrößen und meldet: Bedienelemente außerhalb ihres Moduls, Überlappungen, Text über Text, Fit-all das nicht passt. Jede `UX `-Zeile ist ein Fehler, `UXCOUNT 0` ist das Ziel.

`suite/runall.py` ist der volle Durchlauf, rund 70 Prüfungen, etwa 12 Minuten. Er braucht die vorherige Version als Vergleich. Immer auf einer **eingefrorenen Kopie** laufen lassen und im Hintergrund, nicht auf der Datei, an der gerade gearbeitet wird.

Was darin steckt, in Gruppen:

- **Audio-Identität:** Null-Test (dry/wet 0 muss bitgleich sein), alle Module aus = Eingang, Quelle auf dem Listener im Freifeld = Eingang, Regression gegen die Vorversion.
- **Stabilität:** NaN/Inf am Eingang bringen das Plugin nicht um, Blockgrößen 64/480/2048 liefern dasselbe (Bounce = Echtzeit), Delay-Typen klingen aus.
- **Code:** `casescan.py` (EEL-Bezeichner sind case-insensitiv – zwei Namen, die sich nur in der Groß-/Kleinschreibung unterscheiden, sind derselbe Name), `fncase.py`, `swallow.py` (Code, den ein `//`-Kommentar verschluckt hat), `threadscan.py` (keine Variable, die Audiothread und GUI beide schreiben).
- **GUI:** Flimmerprüfung Frame gegen Frame, Reset beruhigt sich in 3 Frames, Snapshots/Morph/Undo, Zoom, Fit, Reflektoren, Handles, Presets, Learn-Modus.

### Einzeln nützlich

| Skript | Zweck |
|---|---|
| `swallow.py DATEI` | findet Code, der in einem `//`-Kommentar verschwunden ist – passiert beim Einfügen von Kommentaren erschreckend leicht |
| `casescan.py DATEI` | Groß-/Kleinschreibungs-Kollisionen bei EEL-Bezeichnern |
| `threadscan.py DATEI` | Variablen, die @block und @gfx beide schreiben |
| `nulltest.py DATEI` | Bitgleichheit bei dry/wet 0 |
| `fdiff.py 1500x880 …` | Frame-zu-Frame-Unterschiede, findet Flimmern |
| `regress2.py ALT NEU` | Audio-Vergleich der Quellenmodelle mit Raum an |
| `lostcode.py DATEI` | Codeblöcke, die nicht mehr erreicht werden |

---

## 4 · Fallen, die mich Zeit gekostet haben

- **EEL ist case-insensitiv.** `dopHo` und `dopho` sind dieselbe Variable. Deshalb `casescan.py`.
- **`//` frisst den Rest der Zeile.** Ein Kommentar hinter Code in derselben Zeile ist in Ordnung, ein Kommentar *vor* Code in derselben Zeile löscht ihn still. Deshalb `swallow.py`.
- **Funktionen müssen vor ihrer Verwendung definiert sein**, und Code zwischen `@sample` und `@gfx` landet im falschen Abschnitt.
- **GUI- und Audiothread laufen gleichzeitig.** Dieselbe Variable aus beiden zu schreiben erzeugt Fehler, die nur sporadisch auftreten. Deshalb `threadscan.py`.
- **`gfx_mode`** steht nach manchen Zeichenoperationen noch auf additiv – Hintergrundrechtecke werden dann unsichtbar. Vor dem Zeichnen `gfx_mode = 0; gfx_a = 1;` setzen.
- **`–` und ähnliche Escapes** werden in EEL-Strings nicht interpretiert. Nur ASCII in Plugin-Texten.
- **Slidernummern:** `slider N V` in den Skripten ist 0-basiert, `slider 1 9` setzt also `slider2`.

---

## 5 · Inhalt des Pakets

```
README_ysfx.md        diese Datei
render.cpp            das Hostprogramm
mkv.sh                Quelle → Testkopie
shot.py               der übliche Einstieg: rendern mit Skript
uxcheck.py            der UX-Check
suite/                die volle Prüfsuite (runall.py + 57 Einzeltests)
alloff.py calltest.py casescan.py dltest.py fdiff.py lostcode.py
nulltest.py regress2.py swallow.py threadscan.py
                      Helfer, die runall.py aufruft
```

Pfade in `shot.py` und `suite/runall.py` zeigen auf `/home/claude/...` – beim ersten Lauf auf den eigenen Ordner anpassen.
