# 0.374: Learn must not flicker - in a still window every frame is identical (no layout flip between two scales)
import subprocess, sys, os
from PIL import Image, ImageChops
env = dict(os.environ, SRC=sys.argv[1])
bad = []
for (W, H) in [(2000, 1300), (1100, 700), (1600, 1000), (2400, 1400), (1300, 1800), (1920, 1080)]:
    cmds = "var tb_set 1;var tb_basic 0;frame;key 108;" + "frame;" * 6 + "save /home/claude/host/lfk_a.ppm;frame;save /home/claude/host/lfk_b.ppm;frame;save /home/claude/host/lfk_c.ppm"
    subprocess.run(["python3", "shot.py", "lfk_z", str(W), str(H), cmds], capture_output=True, text=True, env=env)
    ims = [Image.open("/home/claude/host/lfk_%s.ppm" % x).convert("RGB") for x in "abc"]
    for i in (1, 2):
        d = ImageChops.difference(ims[i - 1], ims[i]).convert("L").point(lambda v: 255 if v > 8 else 0)
        n = sum(1 for p in d.getdata() if p)
        if n > 50: bad.append((W, H, n))
print("LEARNFLICKER PASS" if not bad else "LEARNFLICKER FAIL %s" % bad)
