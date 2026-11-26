# Side view (3D tab, chip "Side", 0.349): profile - dragging source / listener sets depth + height (the width stays), the barrier line can be moved (0.384: the Side chip moved left - the Reset button is shorter so that Front fits)
import re as _re
def _dn(c):   # 0.357: the page moved down 10 units (12 px at this size) - mouse positions below the top bar move with it
    return _re.sub(r"mouse (\d+) (\d+) ", lambda m: "mouse %s %d " % (m.group(1), int(m.group(2)) + (12 if int(m.group(2)) >= 60 else 0)), c)
import subprocess, sys, re
new = sys.argv[1]
env = dict(__import__("os").environ, SRC=new)
P = "var tb_basic 0;var tb_set 1;var tb_vi 46;var tb_vv 2;frame;frame;mouse 222 62 0 0;frame;mouse 222 62 1 0;frame;mouse 222 62 0 0;frame;frame;frame;mouse 437 62 0 0;frame;mouse 437 62 1 0;frame;mouse 437 62 0 0;frame;frame;frame"
C = P + ";print sidevOn;mouse 550 176 0 0;frame;mouse 550 176 1 0;frame;mouse 470 130 1 0;frame;mouse 470 130 0 0;frame;frame;print slider13;print slider14;print slider15;mouse 420 176 0 0;frame;mouse 420 176 1 0;frame;mouse 640 230 1 0;frame;mouse 640 230 0 0;frame;frame;print slider10;print slider11;print slider12;slider 40 1;frame;frame;frame;print slider42;mouse 486 105 0 0;frame;mouse 486 105 1 0;frame;mouse 600 105 1 0;frame;mouse 600 105 0 0;frame;frame;print slider42"
# 0.352: room dimensions in the side view (host mouse = gfx / 0.8): right wall line -> depth, ceiling line -> height, depth label -> depth, width stays
E = P + ";mouse 683 188 0 0;frame;mouse 683 188 1 0;frame;mouse 780 188 1 0;frame;mouse 780 188 0 0;frame;frame;print eD1;print eW1;mouse 525 105 0 0;frame;mouse 525 105 1 0;frame;mouse 525 80 1 0;frame;mouse 525 80 0 0;frame;frame;print eH2"
E = E.replace("print eD1", "print slider3").replace("print eW1", "print slider2").replace("print eH2", "print slider4")
oe = subprocess.run(["python3", "shot.py", "sdt2", "1100", "700", _dn(E)], capture_output=True, text=True, env=env).stdout
ve = dict((k, float(x)) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", oe))
oke = bool(ve) and ve.get("slider3", 0) > 5 and abs(ve.get("slider2", 0) - 5.5) < 0.01 and ve.get("slider4", 0) > 2.8
o = subprocess.run(["python3", "shot.py", "sdt", "1100", "700", _dn(C)], capture_output=True, text=True, env=env).stdout
v = dict((k, float(x)) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o))
ok = bool(v) and v.get("sidevOn") == 1 and abs(v["slider14"] - 2.25) > 0.5 and abs(v["slider15"] - 1.5) > 0.3 and abs(v["slider13"] - 2.75) < 0.01 and abs(v["slider11"] - 0.25) > 0.3 and abs(v["slider12"] - 1.5) > 0.3 and abs(v["slider10"] - 2.75) < 0.01 and abs(v["slider42"] - 1.25) > 0.5
ok = ok and oke
print("SIDETEST PASS" if ok else "SIDETEST FAIL " + o.replace("\n", " "))
