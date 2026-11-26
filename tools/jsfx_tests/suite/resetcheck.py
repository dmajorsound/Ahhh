# 0.320: after Reset the page settles within 3 frames (no fold animation / flicker) in All, Tabs and Basic
import subprocess, numpy as np, sys
from PIL import Image
src = sys.argv[1]
subprocess.run(["./mkv.sh", src, "t5.jsfx"], capture_output=True)
s = open("t5.jsfx").read()
s = s.replace("gfx_clear = -1;                          // never auto-clear","tb_set ? ( vopt[11] = tb_basic; vopt[3] = 0; tb_v12 > 0 ? vopt[12] = tb_v12 - 1; tb_set = 0; );\ntb_vi > 0 ? ( vopt[tb_vi] = tb_vv; tb_vi = 0; );\ngfx_clear = -1;   // never auto-clear",1)
s = s.replace("@gfx 760 574\n", "@gfx 760 574\ntb_rst ? ( tb_rst = 0; doreset(); );\n", 1) if "function doreset" in s else s
open("t5.jsfx","w").write(s)
bad = []
for name, pre, W, H, mx, my in (("All", "var tb_basic 0\nvar tb_vi 45\nvar tb_vv 1", 1400, 1000, 1078, 22), ("Tabs", "var tb_basic 0\nvar tb_vi 46\nvar tb_vv 1", 1100, 900, 688, 21), ("Basic", "var tb_basic 1", 1000, 800, 699, 21)):
    sc = "var tb_set 1\nvar tb_v12 1\n" + pre + "\nnoise 5 0 /tmp/x.raw\nframe\nframe\nmouse %d %d 1\nframe\nsave /tmp/rcP.ppm\nmouse %d %d 0\n" % (mx, my, mx, my)
    for i in range(8): sc += "frame\nsave /tmp/rc%d.ppm\n" % i
    open("/tmp/rc.txt", "w").write(sc); subprocess.run(["./render0", "t5.jsfx", str(W), str(H), "/tmp/rc.txt"], capture_output=True)
    ims = [np.asarray(Image.open("/tmp/rcP.ppm")).astype(int)] + [np.asarray(Image.open("/tmp/rc%d.ppm" % i)).astype(int) for i in range(8)]
    d = [int((np.abs(ims[i] - ims[i + 1]).sum(2) > 0).sum()) for i in range(8)]
    if max(d[4:]) > 50 or max(d) > 0.12 * W * H: bad.append("%s %s" % (name, d))   # 0.347: no single frame may repaint more than 12 % of the window (the blink)
print("RESETBAD", "; ".join(bad) if bad else "none")
