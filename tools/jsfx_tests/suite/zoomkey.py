# 0.370: key Z in the Tabs - the module alone: the Stage View is gone completely (height 0, no drawing); Z again = the Stage View is back
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
pre = "var tb_set 1;var tb_basic 0;frame;var tb_vi 46;var tb_vv 1;frame;frame;frame;"
def run(c):
    o = subprocess.run(["python3", "shot.py", "zkey", "1100", "700", pre + c], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
a = run("key 122;frame;frame;frame;print vgone;print VH")          # zoomed: gone
b = run("key 122;frame;frame;frame;key 122;frame;frame;frame;print vgone;print VH")   # again: back
ok = a == [1, 0] and len(b) == 2 and b[0] == 0 and b[1] > 100
print("ZOOMKEY PASS" if ok else "ZOOMKEY FAIL %s %s" % (a, b))
