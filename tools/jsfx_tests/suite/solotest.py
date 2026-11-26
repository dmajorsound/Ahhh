# Solo room (0.345): the delay is bypassed too - output identical with the delay on or off; without solo it differs
import numpy as np, subprocess, sys
new = sys.argv[1]
subprocess.run("./mkv.sh %s /tmp/so.jsfx" % new, shell=True, capture_output=True)
n = 48000 * 2; rng = np.random.default_rng(3); L = rng.standard_normal(n) * 0.1; L[int(0.2 * 48000):] = 0
np.stack([L, L], 1).astype(np.float32).tofile('/tmp/so.raw')
def run(dly, solo):
    open("/tmp/so.txt", "w").write("slider 64 %d\nslider 69 300\nvar soloM %d\nframe\nframe\naudio 8 0\nrawin %d /tmp/so.raw /tmp/soo.raw\n" % (dly, solo, n // 256 + 4))
    subprocess.run(['rm', '-f', '/tmp/soo.raw']); subprocess.run(['./render0', "/tmp/so.jsfx", '320', '200', '/tmp/so.txt'], capture_output=True)
    return np.fromfile('/tmp/soo.raw', dtype=np.float32).reshape(-1, 2)
def env(y, t0, t1):
    seg = y[int(t0 * 48000):int(t1 * 48000)]; return 10 * np.log10(np.mean(seg ** 2) + 1e-12)
a, b = run(1, 3), run(0, 3)
c, d = run(1, 0), run(0, 0)
d_solo = abs(env(a, 0.3, 0.6) - env(b, 0.3, 0.6)); d_norm = abs(env(c, 0.3, 0.6) - env(d, 0.3, 0.6))
ok = d_solo < 1.0 and d_norm > 3.0
print("SOLOTEST PASS" if ok else "SOLOTEST FAIL", "echo window level difference: with solo %.2f dB, without solo %.2f dB" % (d_solo, d_norm))
