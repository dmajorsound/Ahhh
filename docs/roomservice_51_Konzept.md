# RoomservicePro – Konzept und Arbeitsplan

Startdokument für das Projekt. Enthält den Stand der Entscheidungen, damit nichts neu verhandelt werden muss. Stand: 23. November 2026 (Beta 11).

---

## 1 · Ausgangslage

**Name:** Die 5.1-Version heißt **RoomservicePro** (seit 23.11.2026; vorher „RoomservicePro“). Sie ist ein eigener FX neben der 1.0 (`desc: RoomservicePro`, Datei `Ahh.jsfx`, GitHub `dmajorsound/RoomservicePro`). Die 1.0 bleibt in bestehenden Projekten unverändert.

**Basis:** `roomservice_1.0_base.jsfx` – die fertige Version 1.0, Stereo in / Stereo out, binauraler Renderer (Variante A, FX-Name `roomservice`). Eine zweite Datei mit `desc: Roomservice - by dmajorsound` ist inhaltlich identisch, nur Beschriftungen sind anders; sie ist nicht die Basis.

**GUI-Mockup:** `roomservice51_gui_mock.jsfx` – Kopie von 1.0, in der die 5.1-Oberfläche **nur gezeichnet** ist (keine Audiofunktion). Zeigt Lautsprecherring in der Stage View und das neue Output-Modul. Zum Anschauen im Host laden, nicht für Audio verwenden.

**Slider-Reihenfolge:** Obwohl RoomservicePro ein eigener FX ist, bleibt die Slider-Reihenfolge der 1.0 erhalten. Neue Slider **nur hinten anhängen**, nie dazwischen einschieben. Letzter belegter Slider in 1.0: **135**; neue beginnen bei 136. Das hält Presets und Automationen der 1.0 übertragbar und macht den Null-Test des Stereo-Pfads gegen die 1.0 direkt möglich.

---

## 2 · Entschiedene Punkte

| Thema | Entscheidung |
|---|---|
| Kanäle | 6 Kanäle Ausgang (5.1), LFE mit eigenem Regler im Output. **7.1 kommt später**: Kanalzahl und Lautsprechergeometrie werden von Anfang an allgemein angelegt (Lautsprecherliste statt fester sechs Kanäle), 7.1 braucht später nur zwei weitere Einträge |
| Ausgabeformat | Wird **gewählt**, nicht automatisch aus der Spur abgeleitet: Schalter **Output: Stereo \| 5.1** (später 7.1). Bei 5.1 liest das Plugin die Quelle von Kanal 1/2 und schreibt auf 6 Kanäle; die Spur muss dafür auf mindestens 6 Kanälen stehen, sonst bleibt der Stereo-Ausgang. Der Stereo-Pfad bleibt unverändert zur 1.0 |
| Center | diskret, mit Regler von Phantom bis diskret |
| Lautsprecher-Layouts | nur zwei: **ITU** (±30° / ±110°, Winkel einstellbar) und **FILM** (Kino aus der Mischposition gesehen: L/R ±25°, C 0°, Ls/Rs als Arrays um ±100°). Beide als Ring um den Listener |
| Lautsprecherring | **sitzt auf dem Listener** (er ist die Mischposition, die Lautsprecher sind seine Abhöre) und dreht mit *Facing* (Default Fixed = zur Leinwandwand). Radius 30 % der kleineren Raumseite, **eine feste Höhe** (Default 1,2 m). Schalter *Ring: Listener \| Room* (Slider 145): **Room** hält den Listener in der Raummitte mit Blick zur Leinwand (auch gegen Automation und Listener-Motion) – die Quelle pannt wie in einem Kino-Panner über die Lautsprecher, der Raum liefert die Akustik aus der Mitte. Barrier funktioniert in beiden Modi (Empfangspunkt ist immer vorhanden). Entfernungsgesetz bleibt physikalisch (ein „Pan only“ kann später dazu) |
| LFE | optional ein-/ausschaltbar, Crossover 80 / 120 Hz, eigener Pegel |
| Motion | **verhält sich gleich wie bisher**, nur mit 5.1-Lautsprecherausgang: Bahnen und Rundfahrten werden über den Lautsprecherring wiedergegeben, die Bedienung und die Bahnlogik ändern sich nicht |
| Output-Modul | behält das Spektrum, dazu **rundes 5.1-Vectorscope** (Kreis mit den Lautsprecherrichtungen als Marken) und sechs Meter L R C LFE Ls Rs |
| Hall | realistisch wie echte 5.1-Reverbs – siehe § 4 |
| Basic Mode | bleibt vorerst erhalten (Arbeitsregel: keine Features streichen) |

---

## 3 · GUI

**Stage View (alle Modi):** Lautsprecherring um den Listener, dreht mit *Facing*; in *Room* mittig und fest, der Listener trägt das Schloss-Symbol. Lautsprecher als aufrechte Quadrate, Film-Arrays als drei Boxen am Ring. Chip oben links zeigt Layout, Winkel, Ringmodus und Höhe (Warnung bei zu wenig Spurkanälen). LFE als kleine Fläche hinter dem Listener am Boden. Im Plan und in 3D sichtbar. Chips in der Quellenzeile: *5.1*, *ITU | Film*, *Listener | Room*.

**Output-Modul (Beta 10, Tab-Layout):** rechts sechs Meter L R C LFE Ls Rs mit einem gemeinsamen Peak-Hold, Mitte das Spektrum, dazwischen das runde Vectorscope (Ring mit den Lautsprecherrichtungen, Pegelbalken je Lautsprecher nach innen, Energiepunkt mit Spur, LFE-Balken rechts). Untere Zeile in 5.1: *LFE* on/off, *80 | 120*, *Level*, *Center phantom … discrete*; die Korrelationsanzeige weicht. *Format*, *Speakers*, *Ring* und *Snap* bleiben als Chips in der Stage View.

**Nicht ändern:** Fit-Verhalten, Zoom (Z, Mausrad), Fold-Pfeile in Basic, Tooltips, Farbschema, runde Power-Buttons. Kein Orange/Braun. Text darf nie über Text liegen.

---

## 4 · Audio

Der Kern des Umbaus. In 1.0 ist der Renderer **binaural**: pro Tap seitlicher Winkel, ITD, Nahfeld-ILD und Kopfschatten-Filter. Für Lautsprecher ist das falsch – das macht der Kopf im Abhörraum selbst. Also zwei Pfade.

1. **Pfadumschaltung.** Ausgabeformat Stereo → bestehender Pfad unverändert. Ausgabeformat 5.1 → neuer geometrischer Pfad.
2. **Direktschall.** Umgesetzt (Beta 5): paarweises Constant-Power-Panning zwischen den zwei Lautsprechern, die die Einfallsrichtung am Listener einschließen; ohne Ohr-Cues (ITD, Kopfschatten, Nahfeld-ILD). *Center*-Regler blendet leistungsgleich zwischen Phantom (L/R) und diskret (C). Quelle über dem Kopf: gleichmäßig auf alle fünf.
3. **Frühe Reflexionen.** Die Spiegelschallquellen liegen schon vor. Jede Reflexion bekommt ihre tatsächliche Einfallsrichtung und wird per VBAP auf das nächstliegende Lautsprecherpaar verteilt – eine Reflexion von der rechten Wand landet rechts bzw. hinten rechts.
4. **Späte Fahne dekorreliert.** Umgesetzt (Beta 6): vorderes Netz 8 Linien mit drei orthogonalen Ausgängen (L, R, C −6 dB), **Rear-Netz** 8 eigene Linien (andere Längenverhältnisse) mit zwei Ausgängen für Ls/Rs – 16 Linien gesamt, alle fünf Kanäle paarweise unkorreliert (|r| < 0,15 gemessen). Das ist der entscheidende Punkt: echte 5.1-Reverbs umhüllen, weil die fünf Kanäle zueinander unkorreliert sind. Verzögerte Kopien desselben Signals wären ein Phasenfilter, kein Raum.
5. **Hinten später und dunkler.** Umgesetzt: Rear-Netz 10 ms später gespeist, Höhen-RT ×0,9 / ×0,8 / ×0,7 bei 2 / 4 / 8 kHz, gleiche Energie wie vorn.
6. **LFE** nur aus dem Direktschall, Tiefpass bei 80 bzw. 120 Hz (Linkwitz-Riley 4. Ordnung), eigener Pegel. Kein Hall im LFE. Umgesetzt (Beta 9): nimmt die Limiter-Gain mit, speist den Detektor nicht.
7. **Downmix-Kontrolle.** ITU-Downmix gegenprüfen, dass die Dekorrelation keine Kammfilter erzeugt.
8. **7.1-Vorbereitung.** Panner, Reflexionsverteilung und FDN-Ausgänge arbeiten über die Lautsprecherliste (Anzahl und Richtungen), nicht über feste Kanäle. Die Anzahl der dekorrelierten FDN-Ausgänge folgt der Lautsprecherzahl.

---

## 5 · Arbeitsschritte

1. `in_pin` / `out_pin` auf 6 Kanäle, Kanalerkennung, Ausgabeformat-Schalter, Fallback auf Stereo. ✔
2. Lautsprechergeometrie: Layout ITU/FILM, Winkel, Ring am Listener / in der Raummitte, feste Höhe, als Lautsprecherliste. Slider ab 136 aufwärts. ✔
3. Stage-View-Zeichnung aus dem Mockup in die echte Datei übernehmen. ✔
4. VBAP-Panner, Direktschall und frühe Reflexionen auf den neuen Pfad. ✔ (Beta 5)
5. FDN erweitern, fünf dekorrelierte Ausgänge, Rear-Versatz. ✔ (Beta 6)
6. LFE-Zweig mit Crossover. ✔ (Beta 9)
7. Output-Modul: sechs Meter, rundes Vectorscope, neue Regler. ✔ (Beta 10, Tab-Layout; das Knob-Layout des Output-Moduls zeigt weiterhin nur L/R)
8. Tests: Null-Test Stereo-Pfad gegen 1.0 (muss identisch bleiben), Kanalzuordnung, Downmix, Korrelation der fünf Kanäle, CPU.

---

## 6 · Offene Punkte

- Der Stereo-Ausgang bleibt der binaurale Pfad der 1.0. Soll er später zusätzlich ein Lautsprecher-Stereo (ohne Kopfmodell) anbieten?
- *Pan only* im Room-Modus (Direktschall ohne Entfernungsgesetz, wie ein Atmos-Panner)?
- Quelle hinter dem Listener ist durch die Quellrichtcharakteristik (zur oberen Wand) ~10 dB leiser – 1.0-Verhalten, in 5.1 ggf. zu viel.
- CPU: 5.1 braucht etwa 4,1 ms pro 256er-Block (Stereo 2,3; Budget 5,3 bei 48 kHz). Reserven: zweiter Tap-Read, Scattering.

Entschieden und aus der Liste entfernt: Verhalten bei Stereospur (Ausgabeformat wird gewählt, siehe § 2), Motion (gleich, siehe § 2), 7.1 (kommt später, siehe § 2).

---

## 7 · Arbeitsregeln aus der 1.0-Session

- Antworten auf Deutsch, Plugin-Texte in amerikanischem Englisch.
- Jede Lieferung bekommt eine neue Betanummer an **drei** Stellen: `desc:` (Zeile 1 – aber ohne Versionsnummer im Namen!), `//version:` (Zeile 4), `#verstr` im `@init`.
- Vor jeder Lieferung: UX-Check (`uxcheck.py` → UXCOUNT 0) und die volle Testsuite (`suite/runall.py`), auf einer eingefrorenen Kopie im Hintergrund.
- **Stand der Testwerkzeuge (4.11.2026):** ysfx und `render0` sind gebaut, der UX-Check besteht auf der 1.0 (UXCOUNT 0). Die Suite bestand auf der unveränderten 1.0 zunächst nur 44 von 71 Prüfungen; die 27 Fehler waren die Ausgangslage (Free field und Reflektoren, Motion-Stop, Motion-Position, Doppler, Solo, Snapshots/@serialize, „alle Module aus = Eingang", Szenen 3 und 7, Seitenansicht, einige Zoom-/Fit-Tests). Ursache war das 64-Slider-Limit des ysfx-Hosts (auf 256 gepatcht); seitdem 69 von 71 auf der 1.0, offen bleiben reflector und ffsound.
- Ehrliche Berichte: es wird nur im Linux-ysfx-Host getestet, nie in REAPER gehört. Das gehört in jede Antwort.
- Qualität vor CPU, keine Features streichen, keine Phasenprobleme.
- **Stand der Tests (6.11.2026, Beta 7):** Suite 74/76 auf der Pro (die 2 Fehler reflector/ffsound fallen auch auf der 1.0, Ursache offen); Stereo-Pfad bitgleich zur 1.0. Pro-Tests: `prostest.py` (Pins, Pass-through, Null-Test), `geotest.py` (Ring), `pantest.py` (5.1-Panning, Motion), `tailtest.py` (Korrelation, Rear-Offset, Downmix), `progui.py` (Chips).
- Slider: 136 Output, 137 Layout, 138/139 ITU-Winkel, 140 Höhe, 141 LFE, 142 Crossover, 143 LFE-Pegel, 144 Center, 145 Ring, 146 Snap to speaker (Beta 8: Direktschall hart auf den nächsten Lautsprecher, 6° Hysterese, Reflexionen/Hall bleiben geometrisch).
- Tests ergänzt: `lfetest.py` (LFE), Snap-Fälle in `pantest.py`, Output-Tab in `progui.py`. Stand Beta 10: Suite 75/77.
