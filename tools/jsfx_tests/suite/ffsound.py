# 0.358: Free field - the ground sounds different (Off < Snow < Grass < Hard: depth of the comb filter), everything stays finite
import numpy as np, subprocess, sys, os
new = sys.argv[1]
subprocess.run(["./mkv.sh", new, "rs_ffs.jsfx"], check=True)
def run(g):
    ex = "slider 1 30\nslider 2 30\nslider 9 5\nslider 10 4\nslider 11 1.6\nslider 12 5\nslider 13 12\nslider 14 1.6\n"
    open('/tmp/ffs.txt','w').write("slider 0 1\nslider 118 %d\n%s\nplay 1 0\naudio 4 0\nrawin 1100 /home/claude/host/imp.raw /tmp/ffs.raw\n" % (g, ex))
    if os.path.exists('/tmp/ffs.raw'): os.remove('/tmp/ffs.raw')
    subprocess.run(['./render0', 'rs_ffs.jsfx', '300', '200', '/tmp/ffs.txt'], capture_output=True, text=True)
    return np.fromfile('/tmp/ffs.raw', np.float32).reshape(-1, 2).astype(float)
ys = [run(g)[:6000, 0] for g in range(4)]
f = np.fft.rfftfreq(16384, 1 / 48000); m = (f > 200) & (f < 8000)
cd = []
for y in ys:
    d = 20 * np.log10(np.abs(np.fft.rfft(y, 16384))[m] + 1e-12); cd.append(np.percentile(d, 95) - np.percentile(d, 5))
ok = all(np.isfinite(y).all() for y in ys) and cd[3] > cd[0] + 0.8 and cd[2] > cd[3] + 1.0 and cd[1] > cd[2] + 5
print("FFSOUND PASS" if ok else "FFSOUND FAIL", "comb depth Off/Hard/Grass/Snow = %s" % " ".join("%.1f" % c for c in cd))
