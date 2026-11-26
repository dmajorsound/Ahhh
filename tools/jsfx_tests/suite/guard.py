# 0.372 Input Guard: off = the input is not touched (a loud input stays loud); on = a hot input is bent below 0 dBFS, a normal input
# (peaks under -1 dBFS) comes out unchanged
import numpy as np, subprocess, sys, re
src = open(sys.argv[1]).read()
src = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', src)
anchor = 'gfx_clear = -1;                          // never auto-clear'
assert anchor in src
src = src.replace(anchor, 'tb_g > 0 ? ( vopt[68] = tb_gv; tb_g = 0; );\n' + anchor, 1)
tail = "(1 - igT) * igE / (1 + igE)); );\n);"   # end of the guard block in @sample: the probe keeps the largest value that goes on into the engine
assert tail in src
src = src.replace(tail, tail + "\ntb_pk = max(tb_pk, max(abs(inL), abs(inR)));", 1)
open('/tmp/gd.jsfx', 'w').write(src)
n = 48000 * 2
t = np.arange(n) / 48000.0
def run(amp, ing, guard):
    x = (amp * np.sin(2 * np.pi * 220 * t)).astype(np.float32)
    np.stack([x, x], 1).tofile('/tmp/gd.raw')
    open('/tmp/gd.txt', 'w').write("var tb_g 1\nvar tb_gv %d\nvar slider40 %g\nvar slider23 0\nframe\nframe\naudio 8 0\nrawin %d /tmp/gd.raw /tmp/gdo.raw\nprint tb_pk\n" % (guard, ing, n // 256 + 4))
    subprocess.run(['rm', '-f', '/tmp/gdo.raw']); r = subprocess.run(['./render0', '/tmp/gd.jsfx', '320', '200', '/tmp/gd.txt'], capture_output=True, text=True).stdout
    return float(re.search(r'tb_pk = ([-0-9.e+]+)', r).group(1))
hot_off, hot_on = run(0.9, 12, 0), run(0.9, 12, 1)
nrm_off, nrm_on = run(0.5, 0, 0), run(0.5, 0, 1)
ok = hot_off > 3.0 and hot_on < 1.001 and hot_on > 0.95 and abs(nrm_off - 0.5) < 0.001 and abs(nrm_on - 0.5) < 0.001
print("GUARD PASS" if ok else "GUARD FAIL", "hot input 3.6: peak off %.3f / on %.3f; normal input 0.5: off %.4f / on %.4f" % (hot_off, hot_on, nrm_off, nrm_on))
