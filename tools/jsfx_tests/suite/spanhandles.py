# 0.389: stereo handles in the Stage View - the width goes down to 0 % (the handles stay at 0 %), Shift = fine, a detent at 100 %;
# double-click = 100 % <-> 0 %, Alt+click = 100 %, Ctrl/Cmd+click = 0 %; a handle on a room edge: its tooltip (not the edge's)
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(c, pre="var tb_dark 1;var tb_set 1;var tb_basic 0;frame;frame;frame;"):
    o = subprocess.run(["python3", "shot.py", "sph", "1100", "700", pre + c], capture_output=True, text=True, env=env).stdout
    return [float(v) for k, v in re.findall(r"(\S+) = ([-0-9.e]+)", o)]
bad = []
v = run("mouse 572 126 1 0;frame;mouse 566 126 1 0;frame;mouse 550 126 1 0;frame;getslider 97;mouse 550 126 0 0;frame;frame;print spX2")
if len(v) != 2 or v[0] != 0 or abs(v[1] - 424) > 1: bad.append("to zero %s" % v)   # 0 %: the handles 16 px from the ball (100 %: 18 px) + a thin ring = mono
v = run("mouse 572 126 1 0;frame;mouse 572 126 0 0;frame;mouse 572 126 1 0;frame;mouse 572 126 0 0;frame;frame;getslider 97;print drag;mouse 530 126 1 0;frame;mouse 530 126 0 0;frame;mouse 530 126 1 0;frame;mouse 530 126 0 0;frame;frame;getslider 97")
if v != [0, 0, 100]: bad.append("double-click %s" % v)
v = run("mouse 572 126 1 2;frame;mouse 572 126 0 0;frame;frame;getslider 97;mouse 530 126 1 4;frame;mouse 530 126 0 0;frame;frame;getslider 97")
if v != [0, 100]: bad.append("alt / ctrl %s" % v)
v = run("mouse 572 126 1 0;frame;mouse 580 126 1 1;frame;mouse 592 126 1 1;frame;getslider 97;mouse 592 126 0 0;frame")
if len(v) != 1 or not (115 < v[0] < 130): bad.append("shift fine %s" % v)
v = run("mouse 632 143 0 0;frame;frame;print ehv;print spHov", "var tb_dark 1;var tb_set 1;var tb_basic 0;var tb_tips 1;var tb_vi 40;var tb_vv 1;slider 9 5.0;slider 10 0.3;frame;frame;frame;")
if v != [-1, 1]: bad.append("tooltip on the edge %s" % v)
print("SPANHANDLES PASS" if not bad else "SPANHANDLES FAIL " + "; ".join(bad))
