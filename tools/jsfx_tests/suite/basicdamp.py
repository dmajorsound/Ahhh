# 0.386: Basic Barrier - the bar beside Open is Damp (dB, slider44) for wall, window and door; Learn shows the reflectors
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(c):
    return subprocess.run(["python3", "shot.py", "bdp", "1100", "700", c], capture_output=True, text=True, env=env).stdout
bad = []
for b in (1, 2, 3):
    o = run("var tb_dark 1;var tb_set 1;var tb_basic 1;frame;slider 40 %d;frame;frame;mouse 198 632 0 0;frame;mouse 198 632 1 0;frame;mouse 194 632 1 0;frame;mouse 150 632 1 0;frame;mouse 150 632 0 0;frame;getslider 43;getslider 96" % b)
    v = dict((k, float(x)) for k, x in re.findall(r"(slider\d+) = ([-0-9.e]+)", o))
    if not (5 < v.get("slider43", 25) < 20) or v.get("slider96") != 100: bad.append("type %d: %s" % (b, v))
o = run("var tb_dark 1;var tb_set 1;var tb_basic 0;slider 0 1;frame;slider 119 1;slider 120 3;slider 121 2;slider 122 60;slider 123 6;frame;key 108;frame;frame;frame;frame;print learn;print rflHv0")
if "learn = 1" not in o or "rflHv0 = 1" not in o: bad.append("learn reflectors " + o.strip()[-60:])
print("BASICDAMP PASS" if not bad else "BASICDAMP FAIL " + "; ".join(bad))
