# (0.387: the corner moved - the free field 3D view fits the area now, not the room height)
# 0.369: in the zoomed 3D view (the view alone over the whole window) the free field keeps its handles: the corner handle scales the
# area (like a room corner) and the reflector handle R2 moves - the same as in the normal view
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
base = "var tb_set 1;var tb_basic 0;frame;mouse 546 380 1 0;frame;mouse 546 380 0 0;frame;frame;var tb_vi 46;var tb_vv 15;frame;frame;mouse 222 75 1 0;frame;mouse 222 75 0 0;frame;var zoomv 1;frame;frame;"
corner = "mouse 1037 612 0 0;frame;mouse 1037 612 1 0;frame;mouse 1055 622 1 0;frame;mouse 1080 640 1 0;frame;mouse 1080 640 0 0;frame;frame;print slider2;print slider3;"
def run(c):
    o = subprocess.run(["python3", "shot.py", "zff", "1100", "700", base + c], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
v = run(corner)
ok = len(v) == 2 and v[0] > 21 and v[1] > 31
# the screenshot of the reflector drag is checked by the position of R2: compare the picture before / after is not possible here, so the
# probe is the area only - the reflector handle uses the same code path as the normal view (suite REFLGUI)
# 0.370: also in Basic (the zoomed Stage View shows the scale handle in the corner of the floor)
basic = "var tb_set 1;var tb_basic 1;slider 0 1;frame;frame;var zoomv 1;frame;frame;frame;mouse 796 601 0 0;frame;mouse 796 601 1 0;frame;mouse 820 615 1 0;frame;mouse 850 630 1 0;frame;mouse 850 630 0 0;frame;frame;print slider2;print slider3"
o = subprocess.run(["python3", "shot.py", "zffb", "1100", "700", basic], capture_output=True, text=True, env=env).stdout
vb = [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
okb = len(vb) == 2 and (vb[0] > 5.6 or vb[1] > 4.6)
print("ZOOMFF PASS" if ok and okb else "ZOOMFF FAIL %s %s" % (v, vb))
