# 0.385: the reflectors are automatable - sliders 120 … 134 mirror vopt[RFB …]: host -> reflector (audio and GUI thread),
# GUI -> slider, older projects (rfPush) -> the loaded reflectors go into the sliders
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
anchor = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(anchor, 'tb_r > 0 ? ( vopt[RFB + tb_ri] = tb_rv; tb_r = 0; );\n' + anchor, 1)
open('/tmp/rfa.jsfx', 'w').write(src)
env = dict(os.environ, SRC='/tmp/rfa.jsfx')
def run(c):
    o = subprocess.run(["python3", "shot.py", "rfa", "900", "600", c], capture_output=True, text=True, env=env).stdout
    return dict((k, float(v)) for k, v in re.findall(r"(\S+) = ([-0-9.e]+)", o)), o
bad = []
# 1 host (audio thread): slider 121 (R1 X) = 7.5, R1 on (Facade), length 6
d, o = run("var tb_dark 1;slider 0 1;frame;audio 2 0;slider 119 1;slider 120 7.5;slider 123 6;audio 2 0;print vopt;vmem vopt 52 6")
m = re.search(r"vopt\[52\.\.\]: ([-0-9. e]+)", o); v = [float(x) for x in m.group(1).split()] if m else []
if v[:2] != [1, 7.5] or v[4] != 6: bad.append("audio pull %s" % v)
# 2 host while the audio is stopped: GUI frame pulls
d, o = run("var tb_dark 1;slider 0 1;frame;slider 121 3.25;slider 131 -6;frame;vmem vopt 52 15")
m = re.search(r"vopt\[52\.\.\]: ([-0-9. e]+)", o); v = [float(x) for x in m.group(1).split()] if m else []
if len(v) < 15 or v[2] != 3.25 or v[12] != -6: bad.append("gfx pull %s" % v)
# 3 GUI -> slider (R2 height 9.5, level R2 3)
d, o = run("var tb_dark 1;slider 0 1;frame;audio 2 0;var tb_ri 11;var tb_rv 9.5;var tb_r 1;frame;var tb_ri 13;var tb_rv 3;var tb_r 1;frame;audio 2 0;getslider 130;getslider 132;vmem vopt 52 15")
if d.get("slider130") != 9.5 or d.get("slider132") != 3: bad.append("push %s" % d)
# 4 an older project: the loaded reflectors win over the slider defaults
d, o = run("var tb_dark 1;slider 0 1;frame;audio 2 0;var tb_ri 1;var tb_rv 4.4;var tb_r 1;frame;slider 120 0;var rfLoad 99;audio 2 0;frame;getslider 120;vmem vopt 52 3")
if d.get("slider120") != 4.4: bad.append("old project %s" % d)
print("RFAUTO PASS" if not bad else "RFAUTO FAIL " + "; ".join(bad))
