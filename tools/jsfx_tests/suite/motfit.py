# Fit all (All view): the Motion card (with the tempo tools open) must end inside the page - 0.345 (it was 50 px too tall and cut at the bottom)
import subprocess, sys, re
new = sys.argv[1]
env = dict(__import__("os").environ, SRC=new)
bad = []
for W, H in ((1100, 700), (1400, 1000), (1000, 650), (1600, 900)):
    C = "var tb_basic 0;var tb_set 1;var tb_vi 45;var tb_vv 1;slider 99 1;slider 107 1;var tmbOn 1;frame;frame;var tb_vj 42;var tb_vw 1;frame;sleep 1200;frame;frame;frame;print syM;print shM;print LH;print scmax;print tmbY;print tmbH"
    o = subprocess.run(["python3", "shot.py", "mf", str(W), str(H), C], capture_output=True, text=True, env=env).stdout
    v = dict((k, float(x)) for k, x in re.findall(r"(\w+) = ([-0-9.]+)", o))
    if not v or v["syM"] + v["shM"] > v["LH"] + 0.5 or v["tmbY"] + v["tmbH"] > v["syM"] + v["shM"] + 0.5:
        bad.append("%dx%d %s" % (W, H, v))
print("MOTFIT PASS" if not bad else "MOTFIT FAIL " + " | ".join(bad))
