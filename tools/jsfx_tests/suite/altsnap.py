# 0.374: Alt + double-click on the source sets the listener straight ahead again (Facing Fixed, angle 0) in every Facing mode;
# one Alt click alone changes nothing; a plain double-click still moves the source to the room center; a fresh plug-in starts in dark mode
import subprocess, sys, re, os
env = dict(os.environ, SRC=sys.argv[1])
def run(c):
    o = subprocess.run(["python3", "shot.py", "als", "1100", "700", c], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
pre = "var tb_basic 0;var tb_set 1;"
ok = True; info = []
for (f16, f17) in ((1, -80), (0, 45), (2, 30), (1, 0)):
    r = run(pre + "slider 15 %d;slider 16 %d;frame;frame;frame;mouse 550 127 0 4;frame;mouse 550 127 1 4;frame;mouse 550 127 0 4;frame;mouse 550 127 1 4;frame;mouse 550 127 0 4;frame;frame;print slider16;print slider17" % (f16, f17))
    good = r == [1, 0]; ok &= good; info.append(good)
r = run(pre + "slider 15 1;slider 16 -80;frame;frame;frame;mouse 550 127 0 4;frame;mouse 550 127 1 4;frame;mouse 550 127 0 4;frame;frame;print slider16;print slider17")
ok &= r == [1, -80]
r = run(pre + "frame;frame;frame;mouse 550 127 0 0;frame;mouse 550 127 1 0;frame;mouse 550 127 0 0;frame;mouse 550 127 1 0;frame;mouse 550 127 0 0;frame;frame;print slider10;print slider11")
ok &= len(r) == 2 and abs(r[0] - 2.75) < 0.01 and abs(r[1] - 2.25) < 0.01
d = run("frame;frame;frame;print darkmode")
ok &= d == [1]
# double-click on the listener's facing arrow tip = Facing back to default (Fixed, 0); a single click does nothing
src2 = open(sys.argv[1]).read()
m0 = "dTip = sqrt(sqr(mx - qx) + sqr(my - qy));"
assert m0 in src2
open('/tmp/als2.jsfx', 'w').write(src2.replace(m0, m0 + " tb_tx = gox + qx * gs; tb_ty = goy + qy * gs;", 1))
env2 = dict(os.environ, SRC='/tmp/als2.jsfx')
def run2(c):
    o = subprocess.run(["python3", "shot.py", "als", "1100", "700", c], capture_output=True, text=True, env=env2).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
for (f16, f17) in ((1, 45), (1, -120), (0, 0)):
    t = run2(pre + "slider 15 %d;slider 16 %d;frame;frame;frame;mouse 800 300 0 0;frame;mouse 800 300 1 0;frame;mouse 800 300 0 0;frame;print tb_tx;print tb_ty" % (f16, f17))
    tx, ty = int(round(t[0])), int(round(t[1]))
    c = "slider 15 %d;slider 16 %d;frame;frame;frame;mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;print slider16;print slider17;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;print slider16;print slider17" % (f16, f17, tx, ty, tx, ty, tx, ty, tx, ty, tx, ty)
    r = run2(pre + c)
    good = len(r) == 4 and r[0] == f16 and r[1] == f17 and r[2] == 1 and r[3] == 0
    ok &= good; info.append(("arrow", f16, f17, tx, ty, r))
# reset buttons next to Aim and Facing (room view footer)
m1 = "rsFh = sqr(mx - (VX + VW - 18)) + sqr(my - BRY) < 64;"
assert m1 in src2
open('/tmp/als3.jsfx', 'w').write(src2.replace(m1, m1 + " tb_fx = gox + (VX + VW - 18) * gs; tb_fy = goy + BRY * gs; tb_ax = gox + (VX + VW - 208) * gs;", 1))
env3 = dict(os.environ, SRC='/tmp/als3.jsfx')
def run3(c):
    o = subprocess.run(["python3", "shot.py", "als", "1100", "700", c], capture_output=True, text=True, env=env3).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
st = "slider 15 0;slider 16 45;slider 62 0;slider 60 30;"   # Facing Source, angle 45; Aim Listener, Src angle 30
t = run3(pre + st + "frame;frame;frame;print tb_fx;print tb_fy;print tb_ax")
fx, fy, ax = [int(round(v)) for v in t[:3]]
r = run3(pre + st + "frame;frame;frame;print slider16;print slider17;print slider63;print slider61;mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;print slider16;print slider17;print slider63;print slider61;mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;print slider16;print slider17;print slider63;print slider61" % (fx, fy, fx, fy, fx, fy, ax, fy, ax, fy, ax, fy))
good = len(r) == 12 and r[:4] == [0, 45, 0, 30] and r[4:8] == [1, 0, 0, 30] and r[8:12] == [1, 0, 1, 0]
ok &= good; info.append(("buttons", r))
print("ALTSNAP PASS" if ok else "ALTSNAP FAIL %s %s %s" % (info, r, d))
