# 0.358: Motion on, Moves = Source: dragging the (resting) listener takes the center of the path along - room and free field
import subprocess, sys, re, os
new = sys.argv[1]; env = dict(os.environ, SRC=new)
bad = []
for nm, ff in (("room", 0), ("free field", 1)):
    C = "var tb_basic 0;var tb_set 1;var tb_vi 46;var tb_vv 14;frame;frame;slider 0 %d;slider 99 1;slider 100 0;slider 101 0;slider 102 0.3;slider 106 0;frame;frame;audio 300 0.2;frame;sleep 700;audio 300 0.2;frame;audio 300 0.2;frame;mouse 550 201 0 0;frame;mouse 550 201 1 0;frame;mouse 500 257 1 0;frame;audio 100 0.2;frame;mouse 500 257 0 0;frame;audio 300 0.2;frame;frame;print slider13;print slider14;print mtC1x;print mtC1y" % ff
    o = subprocess.run(["python3", "shot.py", "ml", "1100", "700", C], capture_output=True, text=True, env=env).stdout
    v = [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
    if len(v) != 4 or abs(v[0] - 2.75) < 0.3 or abs(v[2] - v[0]) > 0.05 or abs(v[3] - v[1]) > 0.05: bad.append("%s %s" % (nm, v))
print("MOTLIS PASS" if not bad else "MOTLIS FAIL " + "; ".join(bad))
