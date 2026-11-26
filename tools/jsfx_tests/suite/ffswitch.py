# 0.378: Free field - the ground (and its level) switched while nothing moves takes effect at once (was: only once Motion moved something)
import numpy as np, subprocess, sys, os
src = open(sys.argv[1]).read()
anchor = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(anchor, 'tb_g > 0 ? ( vopt[69] = tb_gv; tb_g = 0; );\n' + anchor, 1)
open('/tmp/ffw.jsfx', 'w').write(src)
subprocess.run(["./mkv.sh", "/tmp/ffw.jsfx", "rs_ffw.jsfx"], check=True, capture_output=True)
ex = "slider 1 30\nslider 2 30\nslider 9 5\nslider 10 4\nslider 11 1.6\nslider 12 5\nslider 13 12\nslider 14 1.6\n"
def run(script):
    if os.path.exists('/tmp/ffw.raw'): os.remove('/tmp/ffw.raw')
    open('/tmp/ffw.txt', 'w').write(script)
    subprocess.run(['./render0', 'rs_ffw.jsfx', '300', '200', '/tmp/ffw.txt'], capture_output=True, text=True)
    return np.fromfile('/tmp/ffw.raw', np.float32).reshape(-1, 2).astype(float)[:6000, 0]
f = np.fft.rfftfreq(16384, 1 / 48000); m = (f > 200) & (f < 8000)
def cd(y): d = 20 * np.log10(np.abs(np.fft.rfft(y, 16384))[m] + 1e-12); return np.percentile(d, 95) - np.percentile(d, 5)
bad = []
for g in (1, 2, 3):
    a = run("slider 0 1\nslider 118 %d\n" % g + ex + "play 1 0\naudio 4 0\nrawin 1100 /home/claude/host/imp.raw /tmp/ffw.raw\n")
    b = run("slider 0 1\nslider 118 0\n" + ex + "play 1 0\naudio 200 0\nslider 118 %d\naudio 200 0\nrawin 1100 /home/claude/host/imp.raw /tmp/ffw.raw\n" % g)
    if abs(cd(a) - cd(b)) > 0.3: bad.append("ground %d: %.1f vs %.1f" % (g, cd(a), cd(b)))
# the level: hard ground, -12 dB set while static = -12 dB from the start
a = run("var tb_g 1\nvar tb_gv -12\nframe\nslider 0 1\nslider 118 1\n" + ex + "play 1 0\naudio 4 0\nrawin 1100 /home/claude/host/imp.raw /tmp/ffw.raw\n")
b = run("slider 0 1\nslider 118 1\n" + ex + "play 1 0\naudio 200 0\nvar tb_g 1\nvar tb_gv -12\nframe\naudio 200 0\nrawin 1100 /home/claude/host/imp.raw /tmp/ffw.raw\n")
if np.max(np.abs(a - b)) > 0.001: bad.append("level: max diff %.4f" % np.max(np.abs(a - b)))
print("FFSWITCH PASS" if not bad else "FFSWITCH FAIL " + "; ".join(bad))
