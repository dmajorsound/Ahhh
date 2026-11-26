# 0.357: Free field tab (switches with Room), Tabs | All | Fit under the view modes, keys 1 … 9
import subprocess, sys, re, os
new = sys.argv[1]; env = dict(os.environ, SRC=new)
def run(cmds, src=None):
    e = dict(env); 
    if src: e["SRC"] = src
    o = subprocess.run(["python3", "shot.py", "ffm", "1100", "700", "var tb_basic 0;var tb_set 1;frame;frame;" + cmds], capture_output=True, text=True, env=e).stdout
    return [float(x) for k, x in re.findall(r"(\w+) = ([-0-9.e]+)", o)]
# since 1.0.1 the view switches sit at 126 + tbOff (design units; the name scales with the window): their screen places
g = run("print tbOff;print gs;print gox;print goy;"); TBO, GS, GOX, GOY = (g + [0, 1, 0, 0])[:4]
def sw(k): return (int((126 + TBO + (0, 36, 71)[k] + 18) * GS + GOX), int(37 * GS + GOY))   # Tabs, All, Fit
def clk(x, y): return "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (x, y, x, y, x, y)
bad = []
# switch: All, Tabs, Fit (Tabs) on / off, Fit (All) on
v = run(clk(*sw(1)) + "print tabm;" + clk(*sw(0)) + "print tabm;" + clk(*sw(2)) + "print mvfit;" + clk(*sw(2)) + "print mvfit;" + clk(*sw(1)) + clk(*sw(2)) + "print mvfit;print tabm")
if v != [0, 1, 1, 0, 1, 0]: bad.append("switch %s" % v)
# the dot of the Free field tab: free field on (room off), again = room back; the Room tab's dot brings the room back
v = run("print slider1;" + clk(545, 379) + "print slider1;" + clk(545, 379) + "print slider1;" + clk(545, 379) + clk(414, 379) + "print slider1")
if v != [0, 1, 0, 0]: bad.append("dots %s" % v)
# keys 1 … 9 (the focus test of the plugin is switched off for the test)
src = open(new).read().replace("kfoc = gfx_getchar(65536); kfoc = kfoc > 0 && (kfoc & 1) && (kfoc & 2);", "kfoc = 1;"); open("/tmp/rs_key2.jsfx", "w").write(src)
exp = [6, 3, 10, 1, 15, 4, 5, 14, 7]; got = []
for i in range(9):
    r = run("key %d;frame;frame;frame;print tabsel" % (49 + i), "/tmp/rs_key2.jsfx"); got.append(r[0] if r else -1)
if got != exp: bad.append("keys %s" % got)
print("FFMODE PASS" if not bad else "FFMODE FAIL " + "; ".join(bad))
