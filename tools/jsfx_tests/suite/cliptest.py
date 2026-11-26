# Zoomed 3D room view (0.350): walls and the barrier face must not reach out of the room view (the top bar stays untouched)
import subprocess, sys, numpy as np
from PIL import Image
new = sys.argv[1]
env = dict(__import__("os").environ, SRC=new)
def shot(name, extra):
    C = "var tb_basic 0;var tb_set 1;var tb_vi 46;var tb_vv 14;slider 1 3.93;slider 2 9.74;slider 3 2.63;slider 40 1;slider 41 1.25;frame;frame;mouse 136 38 0 0;frame;mouse 136 38 1 0;frame;mouse 136 38 0 0;frame;frame;" + extra + "frame;frame;frame"
    subprocess.run(["python3", "shot.py", name, "824", "432", C], capture_output=True, text=True, env=env)
    return np.asarray(Image.open("/home/claude/host/%s.png" % name).convert("RGB")).astype(int)
a = shot("clp_a", ""); b = shot("clp_b", "var vzf 2.26;var vzox -60;var vzoy 40;")
d = int((np.abs(a[0:34] - b[0:34]).sum(2) > 0).sum()); d2 = int((np.abs(a[210:260] - b[210:260]).sum(2) > 0).sum())   # top bar and the tab row under the view
print("CLIPTEST PASS" if d == 0 and d2 == 0 else "CLIPTEST FAIL top bar %d px, tab row %d px" % (d, d2))
