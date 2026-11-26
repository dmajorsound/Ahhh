# Motion off, module open (ghost path, Own spot +, size handle): a ball under the mouse must always be draggable (0.346)
import re as _re
def _dn(c):   # 0.357: the page moved down 10 units (12 px at this size) - mouse positions below the top bar move with it
    return _re.sub(r"mouse (\d+) (\d+) ", lambda m: "mouse %s %d " % (m.group(1), int(m.group(2)) + (12 if int(m.group(2)) >= 60 else 0)), c)
import subprocess, sys, re
new = sys.argv[1]
env = dict(__import__("os").environ, SRC=new)
res = []; bad = False
for name, mv, ard, mx, my, idx in (("listener, Own spot", 1, 1, 550, 189, "slider13"), ("source, Own spot", 0, 1, 550, 114, "slider10"), ("listener, Listener", 1, 0, 550, 189, "slider13"), ("both, Room center", 2, 2, 550, 189, "slider13")):
    B = "var tb_basic 0;var tb_set 1;var tb_vi 46;var tb_vv 14;slider 99 1;slider 100 %d;slider 102 0;slider 103 0.5;slider 106 %d;frame;frame;audio 300 0.2;frame;frame;mouse 1047 96 0 0;frame;mouse 1047 96 1 0;frame;mouse 1047 96 0 0;frame;audio 300 0.2;frame;frame;sleep 700;frame;frame" % (mv, ard)
    C = B + ";print %s;mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse 500 245 1 0;frame;mouse 500 245 0 0;frame;frame;print %s" % (idx, mx, my, mx, my, idx)
    o = subprocess.run(["python3", "shot.py", "bt", "1100", "700", _dn(C)], capture_output=True, text=True, env=env).stdout
    m = re.findall(idx + r" = ([-0-9.e]+)", o)
    ok = len(m) == 2 and abs(float(m[0]) - float(m[1])) > 0.3
    res.append("%s:%s" % (name, "ok" if ok else "STUCK")); bad = bad or not ok
print(("BALLTEST FAIL " if bad else "BALLTEST PASS ") + " ".join(res))
