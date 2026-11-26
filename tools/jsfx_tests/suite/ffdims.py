# 0.387: free field - width / depth labels in the Stage View (drag = area size), no height label; the 3D view fits the area
# (height = what stands there, not the room's ceiling); after Fit a new area size fits again
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(c):
    o = subprocess.run(["python3", "shot.py", "ffd", "1100", "700", c], capture_output=True, text=True, env=env).stdout
    return dict((k, float(v)) for k, v in re.findall(r"(\S+) = ([-0-9.e]+)", o))
bad = []
d = run("var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;frame;frame;frame;print dmwx;print dmdx;print dmhx;mouse 550 286 0 0;frame;mouse 550 286 1 0;frame;print drag;mouse 560 286 1 0;frame;mouse 600 286 1 0;frame;mouse 600 286 0 0;frame;print slider2")
if not (d.get("dmwx", -1) > 0 and d.get("dmdx", -1) > 0 and d.get("dmhx", 0) < -9000): bad.append("labels %s" % d)
if d.get("drag") != 7 or not (6.5 < d.get("slider2", 0) < 7.5): bad.append("label drag %s" % d)
a = run("var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;frame;mouse 222 75 0 0;frame;mouse 222 75 1 0;frame;mouse 222 75 0 0;frame;frame;print pS;print pHt")
b = run("var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 0;frame;mouse 222 75 0 0;frame;mouse 222 75 1 0;frame;mouse 222 75 0 0;frame;frame;print pS;print pHt")
if not (a.get("pS", 0) > b.get("pS", 9) * 1.15 and a.get("pHt", 9) < b.get("pHt", 0)): bad.append("3D fit free %s room %s" % (a, b))
d = run("var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;frame;slider 119 1;slider 120 3;slider 121 2;slider 122 90;slider 123 24;frame;frame;mouse 1052 105 0 0;frame;mouse 1052 105 1 0;frame;mouse 1052 105 0 0;frame;frame;print vzFitOn;slider 2 9;frame;frame;frame;print vzOut")
if d.get("vzFitOn") != 1 or d.get("vzOut") != 0: bad.append("refit %s" % d)
print("FFDIMS PASS" if not bad else "FFDIMS FAIL " + "; ".join(bad))
