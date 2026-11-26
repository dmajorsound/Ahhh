# 0.360: snapshots in Basic work like in Expert: right-click menu, double-click = name dialog
import subprocess, sys, re, os
new = sys.argv[1]
env = dict(os.environ, SRC=new)
def run(cmds):
    o = subprocess.run(["python3", "shot.py", "bsn", "1100", "700", "var tb_basic 1;var tb_set 1;frame;frame;" + cmds], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
H = "mouse 490 27 0 0;frame;frame;"
v = run(H + "mouse 490 27 4 0;frame;mouse 490 27 0 0;frame;print snctx;print snmN;" +        # right-click: menu, empty slot = 2 items
        "mouse 600 300 1 0;frame;mouse 600 300 0 0;frame;print snctx;" +                        # click elsewhere closes it
        H + "mouse 490 27 1 0;frame;mouse 490 27 0 0;frame;mouse 490 27 1 0;frame;mouse 490 27 0 0;frame;frame;print snedit")   # double-click: dialog
ok = v == [1, 2, 0, 1]
print("BASICSNAP PASS" if ok else "BASICSNAP FAIL %s" % v)
