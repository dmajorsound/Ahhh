# 0.389: Basic - every module card has its own fold arrow (Source, Room, Barrier, Output); a folded card lets the one under it
# (same column) move up; Alt+click folds all
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(c):
    o = subprocess.run(["python3", "shot.py", "bfo", "1100", "700", "var tb_dark 1;var tb_set 1;var tb_basic 1;frame;frame;frame;" + c], capture_output=True, text=True, env=env).stdout
    return dict((k, float(v)) for k, v in re.findall(r"(\w+) = ([-0-9.e]+)", o))
clk = "mouse %d 151 0 0;frame;mouse %d 151 1 0;frame;mouse %d 151 0 0;frame;sleep 400;frame;frame;frame;"
pr = "print yS2;print yO2;print hbS;print hbR;print hbB;print hbO;"
bad = []
a = run(pr)
b = run(clk % (90, 90, 90) + pr)
if not (b["hbS"] < 30 and b["hbR"] > 150 and b["yS2"] < a["yS2"] - 100 and abs(b["yO2"] - a["yO2"]) < 1): bad.append("source fold %s %s" % (a, b))
c = run(clk % (400, 400, 400) + pr)
if not (c["hbR"] < 30 and c["hbS"] > 150 and c["yO2"] < a["yO2"] - 100): bad.append("room fold %s" % c)
d = run(clk % (90, 90, 90) + clk % (90, 90, 90) + pr)
if abs(d["hbS"] - a["hbS"]) > 1: bad.append("unfold %s" % d)
print("BASICFOLD PASS" if not bad else "BASICFOLD FAIL " + "; ".join(bad))
