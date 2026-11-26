# Motion circle: the audio position (sx, sy in meters) must lie on the circle around the listener for every Size factor (0.356)
import subprocess, sys, re, os, math
new = sys.argv[1]; env = dict(os.environ, SRC=new)
bad = []
for nm, pre in (("size 1", "frame"), ("size 0.5", "slider 30 0.5"), ("size 2", "slider 30 2"), ("size 3", "slider 30 3")):
  for free in (1, 0):
    C = "var tb_basic 0;var tb_set 1;frame;frame;%s;frame;frame;slider 0 %d;frame;frame;slider 100 0;slider 101 0;slider 102 0.25;slider 106 0;slider 107 0;slider 99 1;frame;frame;audio 300 0.2;frame;sleep 900;audio 300 0.2;frame;audio 300 0.2;frame;print slider31;print slider104;print slider13;print slider14;print sx;print sy;print mtE" % (pre, free)
    o = subprocess.run(["python3", "shot.py", "mp", "1100", "700", C], capture_output=True, text=True, env=env).stdout
    v = dict((k, float(x)) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o))
    if "sx" not in v: bad.append(nm + " no output"); continue
    rs = v["slider31"]; d = math.hypot(v["sx"] - v["slider13"] * rs, v["sy"] - v["slider14"] * rs)
    if abs(d - v["slider104"] * rs) > 0.05 * rs + 0.02 or v["mtE"] < 0.99: bad.append("%s free%d dist %.2f want %.2f" % (nm, free, d, v["slider104"] * rs))
print("MOTPOS PASS" if not bad else "MOTPOS FAIL " + "; ".join(bad)[:400])
