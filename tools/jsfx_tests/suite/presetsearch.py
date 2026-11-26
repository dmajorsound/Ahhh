# 0.388: the preset search finds rooms, my rooms, scenes AND free-field presets ("forest" -> Forest road; Enter loads it)
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(c):
    o = subprocess.run(["python3", "shot.py", "psr", "1100", "700", c], capture_output=True, text=True, env=env).stdout
    return dict((k, float(v)) for k, v in re.findall(r"(\S+) = ([-0-9.e]+)", o))
pre = "var tb_dark 1;var tb_basic 0;var tb_set 1;frame;frame;var rmenu 1;frame;frame;keys %s;frame;frame;frame;print ffpn;print scl0;print scl1;print rmfirst;print rmnone;"
bad = []
d = run(pre % "forest" + "key 13;frame;frame;print isfree;print ffpLast;print rmenu")
if d.get("ffpn") != 1 or d.get("isfree") != 1 or d.get("ffpLast") != 7 or d.get("rmenu") != 0: bad.append("forest %s" % d)
d = run(pre % "street")
if d.get("ffpn") != 3 or d.get("scl0", -1) < 0: bad.append("street %s" % d)
d = run(pre % "party")
if d.get("scl0") != 0 or d.get("rmnone") != 0: bad.append("party %s" % d)
d = run(pre % "xqzw")
if d.get("rmnone") != 1: bad.append("none %s" % d)
d = run(pre % "living")
if d.get("rmfirst", -1) < 0: bad.append("living %s" % d)
print("PRESETSEARCH PASS" if not bad else "PRESETSEARCH FAIL " + "; ".join(bad))
