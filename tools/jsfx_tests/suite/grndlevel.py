# 0.372 Ground level: the ground reflection (Hard) gets deeper / shallower with the level; the other sound stays; 0 dB = unchanged
import numpy as np, subprocess, sys, re, os
src = open(sys.argv[1]).read()
src = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', src)
anchor = 'gfx_clear = -1;                          // never auto-clear'
src = src.replace(anchor, 'tb_g > 0 ? ( vopt[69] = tb_gv; tb_g = 0; );\n' + anchor, 1)
open('/tmp/gl.jsfx', 'w').write(src)
def run(db, g=1):
    ex = "slider 1 30\nslider 2 30\nslider 9 5\nslider 10 4\nslider 11 1.6\nslider 12 5\nslider 13 12\nslider 14 1.6\n"
    open('/tmp/gl.txt','w').write("var tb_g 1\nvar tb_gv %g\nslider 0 1\nslider 118 %d\n%s\nframe\nframe\nplay 1 0\naudio 4 0\nrawin 1100 /home/claude/host/imp.raw /tmp/gl.raw\n" % (db, g, ex))
    if os.path.exists('/tmp/gl.raw'): os.remove('/tmp/gl.raw')
    subprocess.run(['./render0', '/tmp/gl.jsfx', '300', '200', '/tmp/gl.txt'], capture_output=True, text=True)
    return np.fromfile('/tmp/gl.raw', np.float32).reshape(-1, 2).astype(float)[:6000, 0]
off = run(0, 0)
ys = {db: run(db) for db in (-12, 0, 6)}
en = {db: float(np.sqrt(np.mean((y - off) ** 2))) for db, y in ys.items()}
ok = all(np.isfinite(y).all() for y in ys.values()) and en[6] > 1.5 * en[0] and en[0] > 1.5 * en[-12] and en[-12] > 0
print("GRNDLEVEL PASS" if ok else "GRNDLEVEL FAIL", "ground part (rms of Hard minus Off) at -12 / 0 / +6 dB = %.5f %.5f %.5f" % (en[-12], en[0], en[6]))
