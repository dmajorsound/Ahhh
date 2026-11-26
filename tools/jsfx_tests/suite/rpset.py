# 0.379: Reflector setups (free field, Reflectors module): the menu sets both reflectors around the listener, inside the area; Esc closes the menu
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
a = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(a, 'tb_m1 = vopt[RFB]; tb_m2 = vopt[RFB + 6]; tb_x1 = vopt[RFB + 1]; tb_x2 = vopt[RFB + 7]; tb_a1 = vopt[RFB + 3]; tb_off = vopt[RFB + 14]; tb_cur = rpcur(); tb_lx = slider13 * slider31; tb_menu = rpmenu;\n' + a, 1)
open('/tmp/rps.jsfx', 'w').write(src)
env = dict(os.environ, SRC='/tmp/rps.jsfx')
pre = "var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;slider 1 30;slider 2 30;slider 12 15;slider 13 15;slider 9 15;slider 10 13.5;frame;var tb_vi 46;var tb_vv 4;frame;frame;frame;"
def clk(x, y): return "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (x, y, x, y, x, y)
def run(c):
    o = subprocess.run(["python3", "shot.py", "rps", "1100", "700", pre + c], capture_output=True, text=True, env=env).stdout
    return dict((k, float(v)) for k, v in re.findall(r"(tb_\w+) = ([-0-9.e]+)", o))
P = "print tb_m1;print tb_m2;print tb_x1;print tb_x2;print tb_a1;print tb_off;print tb_cur;print tb_lx;print tb_menu"
bad = []
v = run(clk(260, 410) + clk(250, 489) + P)            # Street canyon (both sides)
if not (v['tb_m1'] == 1 and v['tb_m2'] == 1 and abs((v['tb_lx'] - v['tb_x1']) - 6) < 0.01 and abs((v['tb_x2'] - v['tb_lx']) - 6) < 0.01 and v['tb_a1'] == 90 and v['tb_off'] == 0 and v['tb_cur'] == 3 and v['tb_menu'] == 0): bad.append("canyon %s" % v)
v = run(clk(260, 410) + clk(250, 631) + P)            # No reflectors
if not (v['tb_m1'] == 0 and v['tb_m2'] == 0 and v['tb_cur'] == 11): bad.append("none %s" % v)
v = run(clk(260, 410) + "key 27;frame;frame;" + P)    # Esc closes
if v.get('tb_menu') != 0: bad.append("esc %s" % v)
print("RPSET PASS" if not bad else "RPSET FAIL " + "; ".join(bad))
