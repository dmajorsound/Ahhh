# 0.385: Stage View zoom also out (wheel, down to 10 %), "Fit" = area + reflectors in view; reflector handles stay reachable
# (clamped to the view's edge) and their drag does not jump on the grab
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(c):
    o = subprocess.run(["python3", "shot.py", "vzf", "1100", "700", c], capture_output=True, text=True, env=env).stdout
    return o, dict((k, float(v)) for k, v in re.findall(r"(\S+) = ([-0-9.e]+)", o))
pre = "var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;var tb_vi 15;frame;slider 119 1;slider 120 3;slider 121 2;slider 122 60;slider 123 24;slider 124 18;frame;"
bad = []
o, d = run(pre + "frame;frame;print vzOut;mouse 300 150 0 0;frame;wheel -1;frame;frame;print vzf;wheel -6;frame;print vzf")
v = [float(x) for x in re.findall(r"vzf = ([-0-9.e]+)", o)]
if d.get("vzOut") != 1 or len(v) < 2 or not (0.85 < v[0] < 0.9) or not (0.44 < v[1] < 0.46): bad.append("wheel out %s %s" % (d, v))
o, d = run(pre + "mouse 222 75 0 0;frame;mouse 222 75 1 0;frame;mouse 222 75 0 0;frame;frame;vmem rflLHy 0 1;vmem rflHHy 0 1;mouse 1052 105 0 0;frame;mouse 1052 105 1 0;frame;mouse 1052 105 0 0;frame;frame;print vzf;print vzOut")
ly = re.findall(r"rflLHy\[0\.\.\]: ([-0-9.e]+)", o); hy = re.findall(r"rflHHy\[0\.\.\]: ([-0-9.e]+)", o)
if not ly or not (200 < float(ly[0]) <= 240) or not hy or not (75 <= float(hy[0]) < 100): bad.append("handles clamped %s %s" % (ly, hy))
if not (0.1 <= d.get("vzf", 9) < 0.3) or d.get("vzOut") != 0: bad.append("fit %s" % d)
o, d = run(pre + "mouse 222 75 0 0;frame;mouse 222 75 1 0;frame;mouse 222 75 0 0;frame;frame;mouse 556 98 0 0;frame;mouse 556 98 1 0;frame;mouse 556 99 1 0;frame;print drag;vmem vopt 57 1")
h = re.findall(r"vopt\[57\.\.\]: ([-0-9.e]+)", o)
if d.get("drag") != 28 or not h or abs(float(h[0]) - 18) > 0.5: bad.append("height grab %s %s" % (d, h))
print("VZFIT PASS" if not bad else "VZFIT FAIL " + "; ".join(bad))
