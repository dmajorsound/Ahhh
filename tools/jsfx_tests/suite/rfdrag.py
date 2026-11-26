# 0.378: Free field reflectors - grabbed on the dot or anywhere on the panel's foot line, no jump at the grab; they keep their place when the area corner is dragged
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
a = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(a, 'tb_x = vopt[RFB + 1]; tb_y = vopt[RFB + 2]; tb_hx = gox + rflHx0 * gs; tb_hy = goy + rflHy0 * gs; tb_ax = gox + (rflSx0[0] * 0.25 + rflSx1[0] * 0.75) * gs; tb_ay = goy + (rflSy0[0] * 0.25 + rflSy1[0] * 0.75) * gs; tb_fx = gox + ffHx * gs; tb_fy = goy + ffHy * gs; tb_ps = pS * gs; tb_w = slider2;\n' + a, 1)
open('/tmp/rfd.jsfx', 'w').write(src)
env = dict(os.environ, SRC='/tmp/rfd.jsfx')
pre = "var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;frame;var tb_vi 46;var tb_vv 4;frame;frame;frame;mouse 644 376 0 0;frame;mouse 644 376 1 0;frame;mouse 644 376 0 0;frame;frame;frame;"
def run(c):
    o = subprocess.run(["python3", "shot.py", "rfd", "1100", "700", pre + c], capture_output=True, text=True, env=env).stdout
    return dict((k, float(v)) for k, v in re.findall(r"(tb_\w+) = ([-0-9.e]+)", o))
p = run("print tb_x;print tb_y;print tb_hx;print tb_hy;print tb_ax;print tb_ay;print tb_fx;print tb_fy;print tb_ps;print tb_w")
bad = []
ax, ay = int(round(p['tb_ax'])), int(round(p['tb_ay']))
# grab on the panel line (not the dot): a press without moving must not move it; then 40 px to the right
xs = [float(v) for v in re.findall(r"tb_x = ([-0-9.e]+)", subprocess.run(["python3", "shot.py", "rfd", "1100", "700", pre + "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;frame;print tb_x;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;print tb_x" % (ax, ay, ax, ay, ax + 20, ay, ax + 40, ay, ax + 40, ay)], capture_output=True, text=True, env=env).stdout)]
if len(xs) != 2 or abs(xs[0] - p['tb_x']) > 0.01: bad.append("grab jumps %s -> %s" % (p['tb_x'], xs))
elif abs((xs[1] - xs[0]) - 40 / p['tb_ps']) > 0.15: bad.append("moved %.2f m, expected %.2f" % (xs[1] - xs[0], 40 / p['tb_ps']))
# area corner dragged larger: the reflector stays
fx, fy = int(round(p['tb_fx'])), int(round(p['tb_fy']))
r = run("mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;print tb_x;print tb_y;print tb_w" % (fx, fy, fx, fy, fx + 20, fy + 10, fx + 40, fy + 20, fx + 40, fy + 20))
if abs(r['tb_w'] - p['tb_w']) < 0.3: bad.append("area did not change %s" % r)
elif abs(r['tb_x'] - p['tb_x']) > 0.01 or abs(r['tb_y'] - p['tb_y']) > 0.01: bad.append("reflector moved with the area %s -> %s" % ((p['tb_x'], p['tb_y']), (r['tb_x'], r['tb_y'])))
print("RFDRAG PASS" if not bad else "RFDRAG FAIL " + "; ".join(bad))
