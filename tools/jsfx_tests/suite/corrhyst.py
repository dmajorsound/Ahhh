# 0.377: the correlation color zone has a margin - values around 0.3 / 0 no longer flip the color (the mini meter blinked)
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
c = "var tb_dark 1;var tb_basic 0;var tb_set 1;var tb_vi 46;var tb_vv 1;frame;frame;"
seq = [0.5, 0.29, 0.25, 0.31, 0.34, 0.01, -0.01, -0.04, 0.02, 0.05]
for v in seq: c += "var crvSl 1e12;var crvLt 1e12;var crvD %g;var crvS %g;var fullcnt 0;frame;print crvZ;" % (v, v)
o = subprocess.run(["python3", "shot.py", "crh", "1100", "700", c], capture_output=True, text=True, env=env).stdout
z = [float(x) for x in re.findall(r"crvZ = ([-0-9.e]+)", o)]
want = [2, 2, 1, 1, 2, 1, 1, 0, 0, 1]
print("CORRHYST PASS" if z == want else "CORRHYST FAIL %s" % z)
