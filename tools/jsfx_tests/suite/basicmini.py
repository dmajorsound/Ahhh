# 0.359: Basic - the folded room view shows the mini plan (as in Expert)
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
o = subprocess.run(["python3", "shot.py", "bmini", "1100", "700", "var tb_basic 1;var tb_set 1;frame;frame;mouse 699 151 0 0;frame;mouse 699 151 1 0;frame;mouse 699 151 0 0;" + "frame;" * 400 + "print mmW;print mmh;print VH"], capture_output=True, text=True, env=env).stdout
v = [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
print("BASICMINI PASS" if len(v) == 3 and v[0] > 40 and v[1] > 40 and abs(v[2] - 96) < 1 else "BASICMINI FAIL %s" % v)
