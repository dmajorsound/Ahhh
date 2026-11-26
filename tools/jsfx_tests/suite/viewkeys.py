# 0.360: shortcuts B (Basic), E (Expert), L (Learn)
import subprocess, sys, re, os
new = sys.argv[1]
src = open(new).read().replace("kfoc = gfx_getchar(65536); kfoc = kfoc > 0 && (kfoc & 1) && (kfoc & 2);", "kfoc = 1;"); open("/tmp/rs_key4.jsfx", "w").write(src)
env = dict(os.environ, SRC="/tmp/rs_key4.jsfx")
def run(cmds):
    o = subprocess.run(["python3", "shot.py", "vk", "1100", "700", "var tb_basic 0;var tb_set 1;frame;frame;" + cmds], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
def key(c): return "key %d;frame;frame;frame;" % c
P = "print basic;print learn;"
v = run(P + key(98) + P + key(108) + P + key(101) + P + key(66) + P + key(76) + P + key(69) + P)
got = [(int(v[i]), int(v[i + 1])) for i in range(0, len(v), 2)]
exp = [(0, 0), (1, 0), (0, 1), (0, 0), (1, 0), (0, 1), (0, 0)]
print("VIEWKEYS PASS" if got == exp else "VIEWKEYS FAIL %s" % got)
