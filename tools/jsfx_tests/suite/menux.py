# 0.362: the preset windows (room, delay, motion, source) have a close button (x) at their top right corner: it closes without loading anything
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(cmd, names):
    o = subprocess.run(["python3", "shot.py", "mx", "1100", "700", cmd + "".join(";print " + n for n in names)], capture_output=True, text=True, env=env).stdout
    return dict((k, float(q)) for k, q in re.findall(r"(\w+) = ([-0-9.e]+)", o))
B = "var tb_basic 0;var tb_set 1;frame;frame"
def click(x, y): return ";mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame" % (x, y, x, y, x, y)
T = [("room", "", (352, 24), "rmenu", ["roommx", "roommy", "roommw"], ["slider2"], 1),
     ("delay", ";var tb_vi 46;var tb_vv 10;frame;frame", None, "dmenu", ["dpmx", "dpmy", "dpmw"], ["slider65"], 1),
     ("motion", ";var tb_vi 46;var tb_vv 14;frame;frame", (235, 410), "mpmenu", ["mpmx", "mpmy", "mpmw"], ["slider100"], 1),
     ("source", ";var tb_vi 46;var tb_vv 3;frame;frame", (235, 411), "smenu", ["srcmx", "srcmy", "srcmw"], ["slider35"], 1)]
bad = []
for n, pre, op, mv, geo, st, _ in T:
    c0 = B + pre
    c1 = c0 + (click(*op) if op else ";var dmenu 1;frame;frame")
    a = run(c1, [mv, "gs", "gox", "goy"] + geo + st)
    if a.get(mv) != 1: bad.append(n + " did not open %s" % a); continue
    base = run(c0, st)
    x = a["gox"] + (a[geo[0]] + a[geo[2]] - 3) * a["gs"]; y = a["goy"] + (a[geo[1]] + 3) * a["gs"]
    if n == "room": x, y = 891, 44
    b = run(c1 + click(int(x), int(y)), [mv] + st)
    if b.get(mv) != 0 or any(abs(b[k] - base[k]) > 1e-6 for k in st): bad.append(n + " %s %s (x=%d y=%d)" % (a, b, x, y))
print("MENUX PASS" if not bad else "MENUX FAIL %s" % bad)
