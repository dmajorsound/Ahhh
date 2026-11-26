# 0.384: Front view (3D tab, chip "Front"): x to the right, the height up, the depth collapsed; dragging a ball sets left / right and
# the height, the depth stays; the Side view keeps working the other way round; Front chip only when there is room for it
import subprocess, sys, re, os
src = open(sys.argv[1]).read()
a = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(a, 'tb_sx = slider10; tb_sy = slider11; tb_sz = slider12; tb_px = gox + (pX0 + slider10 * rs * pXs + slider11 * rs * pKX) * gs; tb_py = goy + (pY0 + slider11 * rs * pKY - slider12 * pSZ) * gs; tb_fv = frontv; tb_sv = sidev; tb_ps = pS * gs;\n' + a, 1)
open('/tmp/fvw.jsfx', 'w').write(src)
env = dict(os.environ, SRC='/tmp/fvw.jsfx')
P = "print tb_sx;print tb_sy;print tb_sz;print tb_px;print tb_py;print tb_fv;print tb_sv;print tb_ps;"
def run(c, W=1100):
    o = subprocess.run(["python3", "shot.py", "fvw", str(W), "700", c], capture_output=True, text=True, env=env).stdout
    return dict((k, float(v)) for k, v in re.findall(r"(tb_\w+) = ([-0-9.e]+)", o))
bad = []
pre = "var tb_dark 1;var tb_basic 0;var tb_set 1;var tb_vi 40;var tb_vv 1;var sidev 2;frame;frame;frame;"
p = run(pre + P)
if p['tb_fv'] != 1: bad.append("front view not on %s" % p)
else:
    sx, sy = int(round(p['tb_px'])), int(round(p['tb_py']))
    # drag the source 40 px right and 30 px up: x + 40 / ps m, z + 30 / ps m, y unchanged
    r = run(pre + "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (sx, sy, sx, sy, sx + 20, sy - 15, sx + 40, sy - 30, sx + 40, sy - 30) + P)
    dx = (r['tb_sx'] - p['tb_sx']) * (p['tb_ps'] / p['tb_ps']) ; dz = r['tb_sz'] - p['tb_sz']
    if abs(r['tb_sy'] - p['tb_sy']) > 0.001: bad.append("depth changed %.3f -> %.3f" % (p['tb_sy'], r['tb_sy']))
    if abs(dx * p['tb_ps'] - 40) > 3 or abs(dz * p['tb_ps'] - 30) > 3: bad.append("moved dx %.2f dz %.2f (px %.1f / %.1f, want 40 / 30)" % (dx, dz, dx * p['tb_ps'], dz * p['tb_ps']))
# the Side view still moves the depth (and keeps x)
pre2 = "var tb_dark 1;var tb_basic 0;var tb_set 1;var tb_vi 40;var tb_vv 1;var sidev 1;frame;frame;frame;"
p2 = run(pre2 + P)
if p2['tb_fv'] != 0 or p2['tb_sv'] != 1: bad.append("side view not on %s" % p2)
else:
    sx, sy = int(round(p2['tb_px'])), int(round(p2['tb_py']))
    r = run(pre2 + "mouse %d %d 0 0;frame;mouse %d %d 1 0;frame;mouse %d %d 1 0;frame;mouse %d %d 0 0;frame;frame;" % (sx, sy, sx, sy, sx + 30, sy, sx + 30, sy) + P)
    if abs(r['tb_sx'] - p2['tb_sx']) > 0.001 or r['tb_sy'] <= p2['tb_sy'] + 0.1: bad.append("side view drag: x %.2f -> %.2f, y %.2f -> %.2f" % (p2['tb_sx'], r['tb_sx'], p2['tb_sy'], r['tb_sy']))
# a narrow window: no room for Front - it falls back to 3D instead of a hidden state
n = run(pre + P, 800)
if n['tb_sv'] != 0 or n['tb_fv'] != 0: bad.append("narrow window kept Front %s" % n)
print("FRONTVIEW PASS" if not bad else "FRONTVIEW FAIL " + "; ".join(bad))
