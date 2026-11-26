# roomservice pro, Beta 2: the Stage View switches - "5.1" (Output format) and ITU | Film - work by mouse; the ring is drawn only in 5.1;
# stopped audio (no @block) still draws the right layout (the GUI builds its own speaker list)
import subprocess, sys, re
jsfx = sys.argv[1]; res = []
def chk(n, ok, i=""): res.append(ok); print(("PASS " if ok else "FAIL ") + n + ("  - " + i if i else ""))
import os, shutil
subprocess.run(["python3", "shot.py", "zzg", "200", "200", "frame"], env=dict(os.environ, SRC=jsfx), capture_output=True); shutil.copy("t.jsfx", "tgu.jsfx")   # t.jsfx = the plug-in with the test hooks (theme, tab, view)
def click(x, y): return "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (x, y, x, y, x, y)
pre = "var tb_dark 1;var tb_set 1;var tb_basic 0;slider 135 1;frame;frame;"
def run(cmds):
    open("/tmp/tgu.txt", "w").write("\n".join(c for c in cmds.split(";") if c.strip()) + "\n")
    o = subprocess.run(["./render0", "tgu.jsfx", "1500", "880", "/tmp/tgu.txt"], capture_output=True, text=True).stdout
    return [float(x) for x in re.findall(r"slider1(?:3[67]|4[1256]|3|4) = ([-0-9.e]+)", o)] if not getattr(run, "raw", 0) else o
v = run(pre.replace("slider 135 1;", "") .replace("var tb_dark 1", "var tb_dark 1") + "print slider136;print slider137;" + click(481, 361) + "print slider136;print slider137;" + click(600, 361) + "print slider136;print slider137;" + click(546, 361) + "print slider136;print slider137;" + click(481, 361) + "print slider136;print slider137;" + click(481, 361) + "slider 12 4;slider 13 1;" + click(750, 361) + "print slider145;print slider13;print slider14;audio 2 0.1;print slider13;print slider14;" + click(675, 361) + "print slider145;" + click(848, 361) + "print slider146;" + click(848, 361) + "print slider146;")
# the Output tab in 5.1: LFE chip, crossover segp, Center slider (Alt+click = discrete after dragging it)
# the row with the LFE chip, the 80 | 120 switch and the Level slider (1500 x 880, the footer of 1.0.3: y 817)
def oc(dx): return ((55, 100, 150)[dx], 817)
v2 = run(pre + "var tb_vi 46;var tb_vv 7;frame;frame;print slider141;print slider142;" + click(*oc(0)) + "print slider141;" + click(*oc(2)) + "print slider142;" + click(*oc(1)) + "print slider142;" + click(*oc(0)) + "print slider141;")
chk("start: Stereo, ITU", v[:2] == [0, 0], str(v[:2]))
chk("click 5.1: Output format = 5.1", v[2] == 1, str(v[2:4]))
chk("click Film: layout = Film", v[5] == 1, str(v[4:6]))
chk("click ITU: layout = ITU", v[7] == 0, str(v[6:8]))
chk("click 5.1 again: back to Stereo", v[8] == 0, str(v[8:10]))
chk("click Room: ring in the room, the listener (set to 4, 1) is held in the middle (2.75, 2.25) by the audio thread; click Listener: back", v[10] == 1 and abs(v[13] - 2.75) < 1e-6 and abs(v[14] - 2.25) < 1e-6 and v[15] == 0, str(v[10:16]))
chk("click Snap spk: on, click again: off", v[16] == 1 and v[17] == 0, str(v[16:18]))
chk("Output tab, 5.1: LFE chip off / on, crossover 120 / 80", v2[:2] == [1, 0] and v2[2] == 0 and v2[3] == 1 and v2[4] == 0 and v2[5] == 1, str(v2))
# the ring is drawn in 5.1 only: pixel difference of the room view with / without
def shot(sl):
    subprocess.run(["./render0", "tgu.jsfx", "1500", "880", "/tmp/tgs.txt"], capture_output=True)
open("/tmp/tgs.txt", "w").write("var tb_dark 1\nvar tb_set 1\nvar tb_basic 0\nvar pro_on 1\nframe\nframe\nframe\nsave /tmp/tg_off.ppm\nslider 135 1\nframe\nframe\nsave /tmp/tg_on.ppm\nslider 136 1\nframe\nframe\nsave /tmp/tg_film.ppm\n")
shot(0)
from PIL import Image, ImageChops
a = Image.open("/tmp/tg_off.ppm").crop((600, 110, 900, 360)); b = Image.open("/tmp/tg_on.ppm").crop((600, 110, 900, 360)); c = Image.open("/tmp/tg_film.ppm").crop((600, 110, 900, 360))
d1 = ImageChops.difference(a.convert("RGB"), b.convert("RGB")).getbbox(); d2 = ImageChops.difference(b.convert("RGB"), c.convert("RGB")).getbbox()
chk("Stereo: no ring in the Stage View; 5.1: the ring appears (even without a block run)", d1 is not None)
chk("ITU -> Film changes the drawing", d2 is not None)
print("PROGUI PASS" if all(res) else "PROGUI FAIL")
