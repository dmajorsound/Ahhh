# usage: python3 shot.py name W H "cmd;cmd;..."   (builds t.jsfx from roomservice.jsfx, renders, saves name.png)
import sys, subprocess
from PIL import Image
name, W, H, cmds = sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4]
import os
subprocess.run("./mkv.sh %s t.jsfx" % os.environ.get("SRC", "/home/claude/ms/roomservice.jsfx"), shell=True, check=True)
s = open("t.jsfx").read()
s = s.replace("gfx_clear = -1;                          // never auto-clear",
  "tb_set ? ( vopt[11] = tb_basic; vopt[4] = tb_dark; vopt[3] = tb_tips; vopt[1] = tb_paths; vopt[7] = tb_mono; vopt[6] = tb_waves; tb_v12 > 0 ? vopt[12] = tb_v12 - 1; tb_set = 0; );\ntb_vi > 0 ? ( vopt[tb_vi] = tb_vv; tb_vi = 0; );\ntb_vj > 0 ? ( vopt[tb_vj] = tb_vw; tb_vj = 0; );\ntb_ex ? ( vopt[21] = tb_e21; vopt[22] = tb_e22; vopt[23] = tb_e23; vopt[24] = tb_e24; vopt[25] = tb_e25; vopt[26] = tb_e26; vopt[27] = tb_e27; vopt[28] = tb_e28; vopt[29] = tb_e29; vopt[30] = tb_e30; vopt[31] = tb_e31; vopt[32] = tb_e32; vopt[33] = tb_e33; vopt[34] = tb_e34; tb_ex = 0; );\ngfx_clear = -1;   // never auto-clear", 1)
s = s.replace("gfx_clear = -1;   // never auto-clear", "tb_lr > 0 ? ( loadroom(tb_lr - 1); tb_lr = 0; );\ntb_sc > 0 ? ( scnload(tb_sc - 1); tb_sc = 0; );\ngfx_clear = -1;   // never auto-clear", 1)
open("t.jsfx", "w").write(s)
sc = "\n".join(c.strip() for c in cmds.split(";") if c.strip()) + "\nsave /home/claude/host/%s.ppm\n" % name
open("sc_%s.txt" % name, "w").write(sc)
r = subprocess.run(["./render0", "t.jsfx", W, H, "sc_%s.txt" % name], capture_output=True, text=True)
print(r.stdout[-2000:], r.stderr[-2000:])
Image.open("%s.ppm" % name).save("%s.png" % name)
