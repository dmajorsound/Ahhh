# 0.377: All / Fit (Expert) - key Z zooms the module under the mouse, over the Stage View the Stage View; Z again = back
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
res = []
for (x, y) in ((300, 600), (300, 300), (800, 600), (800, 300)):
    for fit in (0, 1):
        c = "var tb_dark 1;var tb_basic 0;var tb_set 1;var tb_vi 45;var tb_vv 1;var tb_vj 42;var tb_vw %d;frame;frame;frame;mouse %d %d 0 0;frame;frame;key 122;frame;frame;print szoom;print zoomv;key 122;frame;frame;print szoom;print zoomv" % (fit, x, y)
        o = subprocess.run(["python3", "shot.py", "zal", "1100", "700", c], capture_output=True, text=True, env=env).stdout
        res.append((x, y, fit, [float(v) for k, v in re.findall(r"(szoom|zoomv) = ([-0-9.e]+)", o)]))
ok = all(len(z) == 4 and z[2] == 0 and z[3] == 0 and (z[0] > 0 or z[1] == 1) for x, y, fit, z in res if not (fit == 1 and x == 300 and y == 600))
ok &= [tuple(r[3][:2]) for r in res if r[2] == 0] == [(1, 0), (10, 0), (5, 0), (0, 1)]
print("ZOOMALL PASS" if ok else "ZOOMALL FAIL %s" % res)
