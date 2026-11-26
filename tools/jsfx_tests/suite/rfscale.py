# 0.384: reflector scale handles in the Stage View - Length (end of the foot line), Height (top edge, 3D), Alt + drag = Angle
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
a = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(a, 'tb_lx = gox + rflLHx[0] * gs; tb_ly = goy + rflLHy[0] * gs; tb_lv = rflLHv[0]; tb_hx = gox + rflHHx[0] * gs; tb_hy = goy + rflHHy[0] * gs; tb_hv = rflHHv[0]; tb_dx = gox + rflHx0 * gs; tb_dy = goy + rflHy0 * gs; tb_X = vopt[RFB + 1]; tb_Y = vopt[RFB + 2]; tb_A = vopt[RFB + 3]; tb_L = vopt[RFB + 4]; tb_H = vopt[RFB + 5]; tb_ps = pS * gs;\n' + a, 1)
open('/tmp/rfs.jsfx', 'w').write(src)
env = dict(os.environ, SRC='/tmp/rfs.jsfx')
pre = "var tb_dark 1;var tb_basic 0;var tb_set 1;slider 0 1;slider 1 30;slider 2 30;slider 12 15;slider 13 15;slider 9 15;slider 10 13.5;frame;var tb_vi 46;var tb_vv 4;frame;frame;frame;mouse 260 410 0 0;frame;mouse 260 410 1 0;frame;mouse 260 410 0 0;frame;mouse 250 471 0 0;frame;mouse 250 471 1 0;frame;mouse 250 471 0 0;frame;frame;frame;"   # setup: House wall beside you (R1 at x = lx - 4, angle 90, length 15)
P = "print tb_lx;print tb_ly;print tb_lv;print tb_hx;print tb_hy;print tb_hv;print tb_dx;print tb_dy;print tb_X;print tb_Y;print tb_A;print tb_L;print tb_H;print tb_ps;"
def run(c):
    o = subprocess.run(["python3", "shot.py", "rfs", "1100", "700", pre + c], capture_output=True, text=True, env=env).stdout
    return [dict((k, float(v)) for k, v in re.findall(r"(tb_\w+) = ([-0-9.e]+)", blk)) for blk in o.split("tb_lx = ")[1:] and ["tb_lx = " + b for b in o.split("tb_lx = ")[1:]]]
bad = []
p = run(P)[0]
if not (p['tb_lv'] == 1 and p['tb_A'] == 90 and abs(p['tb_L'] - 15) < 0.01): bad.append("setup %s" % p)
else:
    lx, ly = int(round(p['tb_lx'])), int(round(p['tb_ly']))
    # length: drag the end handle 30 px further along the line (down, angle 90 = along the depth) -> + 2 x 30 / ps meters, center unchanged
    r = run("mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (lx, ly, lx, ly, lx, ly + 15, lx, ly + 30, lx, ly + 30) + P)[0]
    want = p['tb_L'] + 2 * 30 / p['tb_ps']
    if abs(r['tb_L'] - want) > 0.15 or abs(r['tb_X'] - p['tb_X']) > 0.01 or abs(r['tb_Y'] - p['tb_Y']) > 0.01 or abs(r['tb_A'] - 90) > 0.01: bad.append("length %.2f (want %.2f) X %.2f Y %.2f A %.0f" % (r['tb_L'], want, r['tb_X'], r['tb_Y'], r['tb_A']))
    # angle: Alt + drag on the dot, towards a point 40 px right / 40 px down -> 45 degrees (snapped)
    dx, dy = int(round(p['tb_dx'])), int(round(p['tb_dy']))
    r = run("mouse %d %d 0 4;frame;mouse %d %d 1 4;frame;mouse %d %d 1 4;frame;mouse %d %d 1 4;frame;mouse %d %d 0 4;frame;frame;" % (dx, dy, dx, dy, dx + 20, dy + 20, dx + 40, dy + 41, dx + 40, dy + 41) + P)[0]
    if abs(r['tb_A'] - 45) > 0.01 or abs(r['tb_X'] - p['tb_X']) > 0.01 or abs(r['tb_L'] - p['tb_L']) > 0.01: bad.append("angle %.1f X %.2f L %.2f" % (r['tb_A'], r['tb_X'], r['tb_L']))
    # height (3D): the top handle 20 px up -> + 20 / ps meters
    q = run("var tb_vi 40;var tb_vv 1;frame;frame;frame;" + P)[0]
    if q['tb_hv'] != 1: bad.append("no height handle in 3D %s" % q)
    else:
        hx, hy = int(round(q['tb_hx'])), int(round(q['tb_hy']))
        r = run("var tb_vi 40;var tb_vv 1;frame;frame;frame;mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (hx, hy, hx, hy, hx, hy - 10, hx, hy - 20, hx, hy - 20) + P)[0]
        if not (r['tb_H'] > q['tb_H'] + 0.3) or abs(r['tb_L'] - q['tb_L']) > 0.01: bad.append("height %.2f (was %.2f) L %.2f" % (r['tb_H'], q['tb_H'], r['tb_L']))
print("RFSCALE PASS" if not bad else "RFSCALE FAIL " + "; ".join(bad))
