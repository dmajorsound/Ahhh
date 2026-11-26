# 0.358: Free field tab - knobs, Ground (also the pictures) work; listener can be dragged in the plan and the area grows with Area width / depth
import subprocess, sys, re, os
new = sys.argv[1]; env = dict(os.environ, SRC=new)
def run(cmds):
    o = subprocess.run(["python3", "shot.py", "ffp", "1100", "700", "var tb_basic 0;var tb_set 1;frame;frame;var slider1 1;var tb_vi 46;var tb_vv 15;frame;frame;frame;" + cmds], capture_output=True, text=True, env=env).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
def drag(x, y, y2): return "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (x, y, x, y, x, y - 10, x, y2, x, y2)
def clk(x, y): return "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (x, y, x, y, x, y)
bad = []
v = run(drag(90, 450, 420) + "print slider12;" + drag(205, 450, 410) + "print slider15;" + drag(665, 450, 400) + "print slider117;" + drag(550, 450, 410) + "print slider4;" + drag(780, 450, 410) + "print slider2;" + drag(895, 450, 410) + "print slider3;" + "mouse 435 450 0 0;frame;mouse 435 450 1 0;frame;mouse 460 450 1 0;frame;mouse 470 450 1 0;frame;mouse 470 450 0 0;frame;frame;print slider17")
# (0.376: the Lis angle dial sits between Src angle and Max height - everything right of it moved one place)
if len(v) != 7 or abs(v[0] - 1.5) < 0.05 or abs(v[1] - 1.5) < 0.05 or v[2] < 1 or abs(v[3] - 2.6) < 0.05 or abs(v[4] - 5.5) < 0.05 or abs(v[5] - 4.5) < 0.05 or abs(v[6]) < 0.5: bad.append("knobs %s" % v)
v = run(clk(182, 513) + "print slider119;" + clk(300, 513) + "print slider119;" + clk(122, 513) + "print slider119;" + clk(90, 550) + "print slider119;" + clk(220, 550) + "print slider119;" + clk(350, 550) + "print slider119")
if v != [1, 3, 0, 1, 2, 3]: bad.append("ground %s" % v)
# the area: 30 x 20 m, listener dragged far to the right / down
v = run("var slider2 30;var slider3 20;frame;frame;mouse 450 140 0 0;frame;mouse 450 140 1 0;frame;mouse 600 200 1 0;frame;mouse 640 250 1 0;frame;mouse 640 250 0 0;frame;frame;print slider13;print slider14")
if len(v) != 2 or v[0] < 8 or v[1] < 5: bad.append("listener %s" % v)
print("FFPARAMS PASS" if not bad else "FFPARAMS FAIL " + "; ".join(bad))
