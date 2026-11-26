# Motion Stop: source and listener must be draggable afterwards (0.341) - with audio running and with no audio block after Stop
import re as _re
def _dn(c):   # 0.357: the page moved down 10 units (12 px at this size) - mouse positions below the top bar move with it
    return _re.sub(r"mouse (\d+) (\d+) ", lambda m: "mouse %s %d " % (m.group(1), int(m.group(2)) + (12 if int(m.group(2)) >= 60 else 0)), c)
import subprocess, sys, re
new = sys.argv[1]
env = dict(__import__("os").environ, SRC=new)
P = "var tb_basic 0;var tb_set 1;var tb_vi 46;var tb_vv 14;slider 99 1;slider 101 0;slider 102 0;slider 103 0.5;frame;frame;audio 300 0.2;frame;frame;mouse 1047 96 0 0;frame;mouse 1047 96 1 0;frame;mouse 1047 96 0 0;frame"
D = ";mouse 560 190 0 0;frame;mouse 560 190 1 0;frame;mouse 620 230 1 0;frame;mouse 620 230 0 0;frame;print slider10;print slider11"
res = []
for name, mid in (("idle", ";sleep 700;frame;frame"), ("fade", ";audio 1 0.2")):
    o = subprocess.run(["python3", "shot.py", "stp", "1100", "700", _dn(P + mid + D)], capture_output=True, text=True, env=env).stdout
    m = re.findall(r"slider1[01] = ([-0-9.e]+)", o)
    res.append(name + ":" + (",".join(m) if m else o.replace("\n", " ")))
    ok = len(m) == 2 and abs(float(m[0]) - 2.75) > 0.5
    if not ok: print("STOPTEST FAIL " + " ".join(res)); sys.exit()
print("STOPTEST PASS " + " ".join(res))
