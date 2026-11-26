# 0.362 REFLECTORS (free field): an extra arrival with the delay and level of the image source; none when the reflection point misses the plane
import numpy as np, subprocess, sys, re, os
s = open(sys.argv[1]).read()
s = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', s)
anchor = 'gfx_clear = -1;                          // never auto-clear'
s = s.replace(anchor, 'tb_rf > 0 ? ( vopt[52] = tb_m; vopt[53] = tb_x; vopt[54] = tb_y; vopt[55] = tb_a; vopt[56] = tb_l; vopt[57] = tb_h; tb_rf = 0; );\n' + anchor, 1)
open('/tmp/rfl_t.jsfx', 'w').write(s)
subprocess.run('./mkv.sh /tmp/rfl_t.jsfx /tmp/rfl_t2.jsfx', shell=True, capture_output=True)
def run(m, x, y, a, l, h):
    cmd = "slider 0 1\nslider 1 30\nslider 2 30\nslider 3 12\nslider 9 10\nslider 10 3\nslider 11 1.5\nslider 12 10\nslider 13 12\nslider 14 1.5\nvar tb_m %g\nvar tb_x %g\nvar tb_y %g\nvar tb_a %g\nvar tb_l %g\nvar tb_h %g\nvar tb_rf 1\nframe\nplay 1 0\naudio 600 0\nrawin 1100 /home/claude/host/imp.raw /tmp/rfl.raw\n" % (m, x, y, a, l, h)
    open('/tmp/rfl.txt', 'w').write(cmd)
    if os.path.exists('/tmp/rfl.raw'): os.remove('/tmp/rfl.raw')
    subprocess.run(['./render0', '/tmp/rfl_t2.jsfx', '300', '200', '/tmp/rfl.txt'], capture_output=True)
    return np.fromfile('/tmp/rfl.raw', np.float32).reshape(-1, 2)[:, 0].astype(float)
base = run(0, 0, 0, 0, 0, 0)
hit = run(1, 20, 6, 90, 20, 10)       # a facade at x = 20 (source x 10): image at 30
miss = run(1, 20, 40, 90, 6, 10)      # the same plane, but far away along y: the reflection point is outside its length
d0 = int(np.argmax(np.abs(base)))
dh = hit - base; dm = miss - base
# image: source (10, 3) -> (30, 3); listener (10, 12): direct 9 m, image path 22.8 m: 13.8 m later = 40.4 ms = 1938 samples
exp = d0 + int(round((np.hypot(20, 9) - 9) / 343 * 48000))
w = slice(exp - 30, exp + 1500)
eh = float(np.sum(dh[w] ** 2)); em = float(np.sum(dm[w] ** 2)); pre = float(np.abs(dh[d0 + 100:exp - 60]).max())
mx = float(np.abs(dh).max()); on = int(np.argmax(np.abs(dh) > 0.1 * mx))
ok = abs(on - exp) <= 60 and eh > 1e-9 and em < 0.001 * eh and pre < 0.05 * mx
print("REFLECTOR %s  onset %d (expected %d), energy hit %.2e / miss %.2e, before the onset %.1e" % ("PASS" if ok else "FAIL", on, exp, eh, em, pre))
