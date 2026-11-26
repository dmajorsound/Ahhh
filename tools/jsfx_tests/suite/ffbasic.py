# 0.371: Basic + free field: (1) the scale handle in the corner of the area is there (ffHv), (2) the FREE FIELD title never overlaps the loudness notes
# in the top left corner - it moves right or below them (probe: the note is forced on in an instrumented copy)
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
a = "slider60 >= 0.5 && elT > 0 && time_precise() - elT < 4 ? ("
assert a in src
open('/tmp/ffb_t.jsfx', 'w').write(src.replace(a, "slider60 >= 0.5 ? ("))
def run(f, W, H):
    env = dict(os.environ, SRC=f)
    o = subprocess.run(["python3", "shot.py", "ffb", str(W), str(H), "var tb_set 1;var tb_basic 1;slider 0 1;var slider60 1;frame;frame;frame;print ffHv;print ftx;print fty;print ftw;print ffnR;print ffnB;print VX;print VW"], capture_output=True, text=True, env=env).stdout
    return dict((k, float(x)) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o))
bad = []
for W, H in ((1100, 700), (900, 650), (1400, 900), (760, 574)):
    d = run('/tmp/ffb_t.jsfx', W, H)
    if not d or d.get("ffHv") != 1: bad.append((W, H, "no scale handle", d)); continue
    beside = d["ftx"] - d["ftw"] / 2 >= d["ffnR"] + 8 and d["ftx"] + d["ftw"] / 2 <= d["VX"] + d["VW"] - 8
    below = d["fty"] >= d["ffnB"] + 4
    if not (beside or below): bad.append((W, H, "title overlaps the note", d))
print("FFBASIC PASS" if not bad else "FFBASIC FAIL %s" % bad)
