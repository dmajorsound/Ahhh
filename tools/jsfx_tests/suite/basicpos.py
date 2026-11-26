# Basic: every room preset puts source and listener on the standard places (0.355); Expert keeps them (Keep option)
import subprocess, sys, re, os
new = sys.argv[1]; env = dict(os.environ, SRC=new)
def run(basic, tiles):
    C = "var tb_basic %d;frame;frame;slider 9 1.2;slider 10 3.1;slider 12 4.0;slider 13 1.1;slider 11 1.0;slider 14 1.0;frame;frame" % basic
    for (x, y) in tiles: C += ";mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;frame" % (x, y, x, y, x, y)
    C += ";print slider2;print slider3;print slider4;print slider10;print slider11;print slider12;print slider13;print slider14;print slider15;print slider31"
    o = subprocess.run(["python3", "shot.py", "bpt", "1100", "700", C], capture_output=True, text=True, env=env).stdout
    return dict((k, float(x)) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o))
bad = []
for nm, tile in (("Hallway", (672, 108)), ("Classroom", (550, 108)), ("Small room", (310, 108)), ("Religious", (1015, 108))):
    v = run(1, [tile])
    if not v: bad.append(nm + " no output"); continue
    rs = v["slider31"]
    ok = abs(v["slider10"] - v["slider2"] / 2) < 0.02 and abs(v["slider13"] - v["slider2"] / 2) < 0.02 and abs(v["slider14"] - v["slider3"] / 2) < 0.02 and abs(v["slider15"] - min(1.5, v["slider4"] * rs - 0.1)) < 0.05 and v["slider11"] < v["slider14"] and abs(v["slider11"] - max(v["slider3"] / 2 - 2 / rs, v["slider3"] * 0.05)) < 0.02
    if not ok: bad.append("%s %s" % (nm, v))
print("BASICPOS PASS" if not bad else "BASICPOS FAIL " + "; ".join(bad)[:400])
