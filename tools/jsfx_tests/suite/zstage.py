# 0.389: key Z with the mouse over the Stage View zooms it in every mode (Tabs, Basic, Learn, All); Z again = back;
# elsewhere in Tabs Z still zooms the module; Basic: Z over a card zooms that card (0.389)
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(m, p):
    o = subprocess.run(["python3", "shot.py", "zst", "1100", "700", "var tb_dark 1;var tb_set 1;%s;frame;frame;frame;mouse %s 0 0;frame;frame;key 122;frame;frame;print zoomv;print zmz;key 122;frame;frame;print zoomv;print zmz" % (m, p)], capture_output=True, text=True, env=env).stdout
    return [float(v) for k, v in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
T = [("var tb_basic 0", "500 200", [1, 0, 0, 0]), ("var tb_basic 0", "500 550", [0, 1, 0, 0]), ("var tb_basic 1", "900 400", [1, 0, 0, 0]),
     ("var tb_basic 1", "200 300", [0, 0, 0, 0]), ("var tb_basic 0;key 108;frame;frame;frame", "500 300", [1, 0, 0, 0])]
bad = [(m, p, r) for m, p, e in T for r in [run(m, p)] if r != e]
def runz(p):
    o = subprocess.run(["python3", "shot.py", "zst", "1100", "700", "var tb_dark 1;var tb_set 1;var tb_basic 1;frame;frame;frame;mouse %s 0 0;frame;frame;key 122;frame;frame;print szoom;key 122;frame;frame;print szoom" % p], capture_output=True, text=True, env=env).stdout
    return [float(v) for k, v in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
for p, e in (("150 300", [3, 0]), ("500 300", [1, 0]), ("150 550", [5, 0]), ("500 550", [7, 0])):
    r = runz(p); r != e and bad.append(("basic card", p, r))
print("ZSTAGE PASS" if not bad else "ZSTAGE FAIL %s" % bad)
