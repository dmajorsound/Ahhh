# Motion card (All / Fit all, narrow column): the status text under the knobs must lie inside the card (0.354)
import subprocess, sys, re, os
new = sys.argv[1]; env = dict(os.environ, SRC=new); bad = []
for (W, H) in ((760, 1000), (1100, 700), (1100, 900), (1500, 1000), (900, 800)):
    for fit in (0, 1):
        C = "var tb_basic 0;var tb_set 1;var tb_vi 45;var tb_vv 1;%sslider 99 1;slider 100 0;frame;frame;frame;audio 300 0.2;frame;frame;print mtStyG;print syM;print shM" % ("var tb_vj 42;var tb_vw 1;" if fit else "")
        o = subprocess.run(["python3", "shot.py", "mtc", str(W), str(H), C], capture_output=True, text=True, env=env).stdout
        v = dict((k, float(x)) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o))
        if not v or v["mtStyG"] + 18 > v["syM"] + v["shM"]: bad.append("%dx%d fit%d sty %.0f card end %.0f" % (W, H, fit, v.get("mtStyG", -1), v.get("syM", 0) + v.get("shM", 0)))
print("MOTCARD PASS" if not bad else "MOTCARD FAIL " + "; ".join(bad))
