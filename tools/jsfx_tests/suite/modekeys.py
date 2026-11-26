# 0.358: shortcuts T (Tabs), A (All), F (Fit), 0 (Tabs <-> All with Fit all)
import subprocess, sys, re, os
new = sys.argv[1]
src = open(new).read().replace("kfoc = gfx_getchar(65536); kfoc = kfoc > 0 && (kfoc & 1) && (kfoc & 2);", "kfoc = 1;"); open("/tmp/rs_key3.jsfx", "w").write(src)
env = dict(os.environ, SRC="/tmp/rs_key3.jsfx")
def run(cmds):
    o = subprocess.run(["python3", "shot.py", "mk", "1100", "700", "var tb_basic 0;var tb_set 1;frame;frame;" + cmds], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
def key(c): return "key %d;frame;frame;frame;" % c
P = "print tabm;print mvfit;print ebig;"
v = run(P + key(97) + P + key(116) + P + key(102) + P + key(102) + P + key(97) + key(102) + P + key(116) + P + key(48) + P + key(48) + P)
# start: Tabs, no fit | A: All | T: Tabs | F: Tabs fit on | F: off | A then F: All fit on | T: Tabs | 0: All (Fit all) | 0: Tabs
got = [(int(v[i]), int(v[i + 1]) if v[i] else 1 - int(v[i + 2])) for i in range(0, len(v) - 2, 3)]
exp = [(1, 0), (0, 0), (1, 0), (1, 1), (1, 0), (0, 1), (1, 0), (0, 1), (1, 0)]
print("MODEKEYS PASS" if got == exp else "MODEKEYS FAIL %s" % got)
