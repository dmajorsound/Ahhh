# 0.360: the listener can be moved in the free field - Plan, 3D, All view, Learn, Basic, after a scenario, with the room engine off; a locked ball says so
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def d(pre, x, y):
    c = pre + ";frame;frame;frame;mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;print slider13;print slider14" % (x, y, x, y, x + 20, y - 30, x + 40, y - 50, x + 40, y - 50)
    o = subprocess.run(["python3", "shot.py", "ffl", "1100", "700", c], capture_output=True, text=True, env=env).stdout
    v = [float(q) for k, q in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
    return len(v) == 2 and (abs(v[0] - 2.75) > 0.2 or abs(v[1] - 2.25) > 0.2) if "tb_sc" not in pre else len(v) == 2 and abs(v[0] - 20) > 0.5
B = "var tb_basic %d;var tb_set 1;slider 0 1"
T = [("plan", B % 0 + ";var tb_vi 40;var tb_vv 0", 550, 199), ("3D", B % 0 + ";var tb_vi 40;var tb_vv 1", 550, 159),
     ("All", B % 0 + ";var tb_vi 45;var tb_vv 1", 848, 223), ("Learn", B % 0 + ";var tb_vi 43;var tb_vv 1", 341, 371),
     ("Basic", B % 1, 887, 400), ("room off", B % 0 + ";slider 35 1", 550, 199), ("scenario", B % 0 + ";var tb_sc 11", 550, 223)]
bad = [n for n, pre, x, y in T if not d(pre, x, y)]
print("FFLISTEN PASS" if not bad else "FFLISTEN FAIL %s" % bad)
