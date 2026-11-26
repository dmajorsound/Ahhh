# roomservice pro, Beta 9: the LFE - direct sound only, 80 / 120 Hz Linkwitz-Riley, own level, Off = silent
import numpy as np, subprocess, sys
PRO = sys.argv[1]
def run(nch, x, sl=()):
    subprocess.run(["./mkv.sh", PRO, "tp.jsfx"], check=True)
    x.astype(np.float32).tofile("/tmp/tp_in.raw"); subprocess.run(["rm", "-f", "/tmp/tp_out.raw"])
    subprocess.run(["./render6", "tp.jsfx", str(nch), "/tmp/tp_in.raw", "/tmp/tp_out.raw"] + ["%d=%g" % s for s in sl], capture_output=True)
    return np.fromfile("/tmp/tp_out.raw", dtype=np.float32).reshape(-1, nch)
res = []
def chk(name, ok, info=""): res.append(ok); print(("PASS " if ok else "FAIL ") + name + ("  - " + info if info else ""))
sr = 48000; rng = np.random.default_rng(5); n = 3 * sr // 256 * 256
x = np.zeros((n, 6), np.float32); x[:, 0] = rng.standard_normal(n) * 0.1; x[:, 1] = x[:, 0]
def spec(v):
    F = np.abs(np.fft.rfft(v * np.hanning(len(v)))) ** 2; f = np.fft.rfftfreq(len(v), 1 / sr)
    def band(a, b): m = (f >= a) & (f < b); return 10 * np.log10(F[m].mean() + 1e-30)
    return band
base = [(135, 1), (0, 1), (118, 0), (15, 1), (16, 0), (9, 2.75), (10, 1.25)]   # 5.1, free field, no ground: the direct sound alone
y = run(6, x, base + [(140, 1), (141, 0)])[n // 2:]; b = spec(y[:, 3].astype(np.float64)); bc = spec(y[:, 2].astype(np.float64))
chk("LFE on, 80 Hz: bass present, 24 dB / octave above the crossover (320 Hz 48 dB below 40 Hz, relative to C)", (b(30, 60) - bc(30, 60)) > -3 and (b(300, 340) - bc(300, 340)) < (b(30, 60) - bc(30, 60)) - 40, "40 Hz %.1f dB, 160 Hz %.1f dB, 320 Hz %.1f dB (rel. to C)" % (b(30, 60) - bc(30, 60), b(150, 170) - bc(150, 170), b(300, 340) - bc(300, 340)))
y2 = run(6, x, base + [(140, 1), (141, 1)])[n // 2:]; b2 = spec(y2[:, 3].astype(np.float64))
chk("120 Hz crossover sits higher than 80 Hz (more level at 160 Hz)", b2(150, 170) - b(150, 170) > 8, "%.1f dB more at 160 Hz" % (b2(150, 170) - b(150, 170)))
y3 = run(6, x, base + [(140, 0)])[n // 2:]
chk("LFE off: silent", np.abs(y3[:, 3]).max() == 0)
y4 = run(6, x, base + [(140, 1), (141, 0), (142, -12)])[n // 2:]; b4 = spec(y4[:, 3].astype(np.float64))
chk("LFE level -12 dB", abs((b4(30, 60) - b(30, 60)) + 12) < 0.5, "%.2f dB" % (b4(30, 60) - b(30, 60)))
# in the room: the LFE carries the direct sound only - the tail after a burst stays out of it
xb = np.zeros((n, 6), np.float32); xb[: sr // 2, 0] = rng.standard_normal(sr // 2) * 0.2; xb[:, 1] = xb[:, 0]
yb = run(6, xb, [(135, 1), (31, 3), (9, 2.75), (10, 1.25), (140, 1)]); t0 = sr // 2 + int(0.15 * sr)
tail = 10 * np.log10(np.mean(yb[t0:t0 + sr, 3].astype(np.float64) ** 2) + 1e-30); bur = 10 * np.log10(np.mean(yb[sr // 4:sr // 2, 3].astype(np.float64) ** 2) + 1e-30)
tailL = 10 * np.log10(np.mean(yb[t0:t0 + sr, 0].astype(np.float64) ** 2) + 1e-30); burL = 10 * np.log10(np.mean(yb[sr // 4:sr // 2, 0].astype(np.float64) ** 2) + 1e-30)
chk("in the room: no reverb in the LFE (tail at least 25 dB further below the burst than on L)", (bur - tail) > (burL - tailL) + 25, "LFE burst %.1f tail %.1f, L burst %.1f tail %.1f" % (bur, tail, burL, tailL))
chk("nothing non-finite", all(np.isfinite(v).all() for v in (y, y2, y3, y4, yb)))
print("LFETEST PASS" if all(res) else "LFETEST FAIL")
