# 0.378: Free field - the Reflectors tab has a round on / off button like Barrier (none set: on = R1 becomes a facade)
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
a = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(a, 'tb_r = vopt[RFB + 14]; tb_m = vopt[RFB];\n' + a, 1)
open('/tmp/rft.jsfx', 'w').write(src)
env = dict(os.environ, SRC='/tmp/rft.jsfx')
clk = "mouse 644 376 0 0;frame;mouse 644 376 1 0;frame;mouse 644 376 0 0;frame;frame;frame;print tb_r;print tb_m;"
c = "var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;frame;var tb_vi 46;var tb_vv 4;frame;frame;frame;print tb_r;print tb_m;" + clk * 3
o = subprocess.run(["python3", "shot.py", "rft", "1100", "700", c], capture_output=True, text=True, env=env).stdout
v = [float(x) for x in re.findall(r"tb_[rm] = ([-0-9.e]+)", o)]
ok = v == [0, 0, 0, 1, 1, 1, 0, 1]
print("RFTAB PASS" if ok else "RFTAB FAIL %s" % v)
