# bounce = real time: the same signal through different block sizes (room, delay, motion with Doppler) must give the same output
import numpy as np, subprocess, sys
jsfx = sys.argv[1]; subprocess.run("./mkv.sh %s /tmp/bt.jsfx" % jsfx, shell=True)
n = 48000 * 4; rng = np.random.default_rng(7); L = (rng.standard_normal(n) * 0.1).astype(np.float32)
np.stack([L, 0.7 * L], 1).astype(np.float32).tofile('/tmp/bt.raw')
import os
cfg = [] if os.environ.get("BASE") else ["slider 99 1", "slider 100 0", "slider 101 0", "slider 102 0.5", "slider 103 2", "slider 117 1"]   # Motion on: circle, 2 m, 0.5 Hz, Doppler natural
res = {}
for bs in (64, 480, 2048):
    steps = n // bs + 4
    open("/tmp/bt.txt", "w").write("bsize %d\n" % bs + "\n".join(cfg) + "\naudio 8 0\nrawin %d /tmp/bt.raw /tmp/bto.raw\n" % steps)
    subprocess.run(['rm', '-f', '/tmp/bto.raw']); subprocess.run(['./render0', '/tmp/bt.jsfx', '320', '200', '/tmp/bt.txt'], capture_output=True)
    res[bs] = np.fromfile('/tmp/bto.raw', dtype=np.float32).reshape(-1, 2)[:n - 4000].astype(float)
def env(y):   # RMS per 50 ms (dB): the audible level movement, not the waveform phase of noise
    k = 2400; m = len(y) // k * k; return 10 * np.log10(np.maximum(1e-12, (y[:m].reshape(-1, k, 2) ** 2).mean(1)))
ref = env(res[64]); worst = 0
for bs in (480, 2048):
    e = env(res[bs]); d = np.abs(e - ref)[10:].max(); worst = max(worst, d); print("block %d vs 64: level envelope max diff %.2f dB" % (bs, d))
print("BLOCKTEST PASS" if worst < 1.0 else "BLOCKTEST FAIL")
