# 0.359: stereo handles of the source - a pure display switch (chip "Handles" + key H), independent of the input signal
import subprocess, sys, re, os
new = sys.argv[1]
src = open(new).read().replace("kfoc = gfx_getchar(65536); kfoc = kfoc > 0 && (kfoc & 1) && (kfoc & 2);", "kfoc = 1;"); open("/tmp/rs_key5.jsfx", "w").write(src)
env = dict(os.environ, SRC="/tmp/rs_key5.jsfx")
def run(cmds):
    o = subprocess.run(["python3", "shot.py", "hd", "1100", "700", "var tb_basic 0;var tb_set 1;frame;frame;frame;" + cmds], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
def key(c): return "key %d;frame;frame;frame;" % c
v = run("print spOk;" + key(104) + "print spOk;" + key(72) + "print spOk;" + key(104) + "print spOk")
print("HANDLES PASS" if v == [1, 0, 1, 0] else "HANDLES FAIL %s" % v)
