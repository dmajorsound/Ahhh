# 0.374: Motion "start" label never sits on the size handle (Both moving, Around = Own spot / Listener, Circle / Square, several start angles)
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
a = 'col(cMUTED, 1); gfx_setfont(7); txt("start", tx, ty, 0);'
assert a in src
src = src.replace(a, a + ' tb_ov += (tx < mtHsx + 7 && tx + 26 > mtHsx - 7 && abs(ty - mtHsy) < 9) ? 1 : 0;', 1)
open('/tmp/mtl.jsfx', 'w').write(src)
env = dict(os.environ, SRC='/tmp/mtl.jsfx')
bad = []
for pat in (0, 5):
  for ar in (0, 1, 2):
    for st in (0, 90, 180, 270):
      for dr in (0, 1):
        cmds = "var tb_dark 0;var tb_set 1;var tb_basic 0;slider 99 1;slider 100 2;slider 101 %d;slider 106 %d;slider 104 %d;slider 105 %d;frame;var tb_vi 46;var tb_vv 14;frame;frame;audio 300 0.2;frame;frame;print tb_ov" % (pat, ar, st, dr)
        o = subprocess.run(["python3", "shot.py", "mtl_z", "1100", "700", cmds], capture_output=True, text=True, env=env).stdout
        m = re.search(r"tb_ov = ([-0-9.e]+)", o)
        if not m or float(m.group(1)) > 0: bad.append((pat, ar, st, dr, m.group(1) if m else None))
print("MTLABEL PASS" if not bad else "MTLABEL FAIL %s" % bad[:6])
