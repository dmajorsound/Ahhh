# 0.360 SCENES: every scene loads the expected barrier / delay / mode / ground, the sound stays finite, audible and not clipped
import numpy as np, subprocess, sys, re
src = open(sys.argv[1]).read()
anchor = "gfx_clear = -1;                          // never auto-clear"
assert anchor in src
src = src.replace(anchor, "tb_sc > 0 ? ( scnload(tb_sc - 1); tb_sc = 0; );\n" + anchor, 1)
open("/tmp/scn.jsfx", "w").write(src)
subprocess.run("./mkv.sh /tmp/scn.jsfx /tmp/scn2.jsfx", shell=True, capture_output=True)
# scene: (barrier type, open %, delay on, free field, ground, source model)
E = [(1,0,0,0,0,6),(1,0,0,0,0,7),(1,0,0,0,0,0),(1,0,1,0,0,6),(3,0,0,0,0,0),(3,12,0,0,0,0),(3,35,0,0,0,7),(3,25,1,0,0,0),
     (2,0,0,0,0,0),(2,20,0,0,0,0),(0,0,1,1,2,0),(0,0,1,1,1,0),(0,0,1,1,1,0),(0,0,0,1,3,0),(0,0,1,0,0,None),(0,0,1,0,0,None),(0,0,0,0,0,None),(0,0,1,0,0,None),
     (0,0,0,0,0,None),(2,0,0,0,0,6),(0,0,0,0,0,None),(0,0,1,0,0,None),(0,0,1,0,0,None),
     (0,0,0,0,0,None),(0,0,1,0,0,None),(3,0,0,0,0,0),(0,0,1,0,0,None),(0,0,1,0,0,None),
     (0,0,0,0,0,None),(0,0,0,0,0,None),(0,0,0,1,2,None),(0,0,1,1,1,None),(0,0,1,0,0,None)]
bad = 0
n = 48000 * 2
rng = np.random.default_rng(3); L = (rng.standard_normal(n) * 0.1).astype(np.float32)
np.stack([L, L], 1).tofile('/tmp/scn.raw')
for k in range(33):
    cmd = "audio 8 0\nvar tb_sc %d\nframe\nframe\n" % (k + 1)
    for sl in (41, 43, 65, 1, 119, 35): cmd += "getslider %d\n" % (sl - 1)
    cmd += "rawin %d /tmp/scn.raw /tmp/scno.raw\n" % (n // 256 + 4)
    open("/tmp/scn.txt", "w").write(cmd)
    subprocess.run(['rm', '-f', '/tmp/scno.raw'])
    r = subprocess.run(['./render0', "/tmp/scn2.jsfx", '760', '574', '/tmp/scn.txt'], capture_output=True, text=True).stdout
    v = [float(x) for x in re.findall(r'slider\d+ = ([-0-9.e+]+)', r)]
    y = np.fromfile('/tmp/scno.raw', dtype=np.float32).reshape(-1, 2)
    fin = bool(np.isfinite(y).all()); pk = float(np.abs(y[-24000:]).max()) if fin else -1
    e = E[k]; ok = len(v) == 6 and int(v[0]) == e[0] and abs(v[1] - e[1]) < 0.5 and int(v[2]) == e[2] and int(v[3]) == e[3] and int(v[4]) == e[4] and (e[5] is None or int(v[5]) == e[5])
    ok = ok and fin and 1e-5 < pk < 1.5
    if not ok: bad += 1; print("scene", k, "FAIL", v, "finite", fin, "peak", pk)
print("SCENES PASS" if bad == 0 else "SCENES FAIL %d" % bad)
