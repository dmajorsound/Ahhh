# roomservice pro, Beta 6: the five tail channels are uncorrelated (front network L R C, rear network Ls Rs), the rear arrives later,
# the ITU downmix has no comb filter, the tail decays as in Stereo
import numpy as np, subprocess, sys
PRO = sys.argv[1]
def run(nch, x, sl=()):
    subprocess.run(["./mkv.sh", PRO, "tp.jsfx"], check=True)
    x.astype(np.float32).tofile("/tmp/tp_in.raw"); subprocess.run(["rm", "-f", "/tmp/tp_out.raw"])
    subprocess.run(["./render6", "tp.jsfx", str(nch), "/tmp/tp_in.raw", "/tmp/tp_out.raw"] + ["%d=%g" % s for s in sl], capture_output=True)
    return np.fromfile("/tmp/tp_out.raw", dtype=np.float32).reshape(-1, nch)
res = []
def chk(name, ok, info=""): res.append(ok); print(("PASS " if ok else "FAIL ") + name + ("  - " + info if info else ""))
sr = 48000; rng = np.random.default_rng(11)
# a 0.5 s noise burst, then 2.5 s of silence: the tail alone after the burst (Decay x 3 for a long tail; source 1 m ahead of the listener)
n = 3 * sr // 256 * 256; x = np.zeros((n, 6), np.float32); x[: sr // 2, 0] = rng.standard_normal(sr // 2) * 0.2; x[:, 1] = x[:, 0]
sl = [(135, 1), (31, 3), (9, 2.75), (10, 1.25), (143, 100)]
y = run(6, x, sl); y2 = run(2, x[:, :2], sl)
t0 = sr // 2 + int(0.15 * sr); t1 = t0 + sr   # 150 ms after the burst (the early reflections are gone) ... 1 s later
T = y[t0:t1].astype(np.float64); names = "L R C LFE Ls Rs".split()
cc = np.corrcoef(T[:, [0, 1, 2, 4, 5]].T); off = cc[~np.eye(5, dtype=bool)]
chk("tail: the five loudspeaker channels are uncorrelated (|r| < 0.15 for every pair)", np.abs(off).max() < 0.15, "max |r| %.3f" % np.abs(off).max())
# cross-correlation front / rear at lags up to 30 ms: no peak (copies of one signal would show one)
xc = [np.corrcoef(T[:-2000, 0], T[k:k + len(T) - 2000, 4])[0, 1] for k in range(0, 1440, 48)]
chk("tail: no delayed copy of the front in the rear (cross-correlation L -> Ls < 0.15 at every lag 0 ... 30 ms)", max(abs(v) for v in xc) < 0.15, "max %.3f" % max(abs(v) for v in xc))
lv = 10 * np.log10(np.mean(T ** 2, 0) + 1e-30); lv2 = 10 * np.log10(np.mean(y2[t0:t1].astype(np.float64) ** 2, 0) + 1e-30)
chk("tail: Ls / Rs within 3 dB of L / R, C 4 ... 8 dB below L / R, the LFE silent", abs(lv[4] - lv[0]) < 3 and abs(lv[5] - lv[1]) < 3 and 4 < lv[0] - lv[2] < 8 and lv[3] < -200, " ".join("%s %.1f" % v for v in zip(names, lv)))
chk("tail: front L / R within 2 dB of the Stereo tail", abs(lv[0] - lv2[0]) < 2 and abs(lv[1] - lv2[1]) < 2, "5.1 %.1f %.1f  stereo %.1f %.1f" % (lv[0], lv[1], lv2[0], lv2[1]))
# decay: energy in 200 ms windows along the tail - the rear decays like the front (slope within 30 %)
def slope(v):
    w = v[: len(v) // 9600 * 9600].reshape(-1, 9600); e = 10 * np.log10(np.mean(w ** 2, 1) + 1e-30); return np.polyfit(np.arange(len(e)), e, 1)[0]
sf, sb = slope(T[:, 0]), slope(T[:, 4])
chk("tail: the rear decays like the front (slope within 30 %)", sf < -0.5 and abs(sb - sf) < 0.3 * abs(sf), "front %.2f dB / 200 ms, rear %.2f" % (sf, sb))
# rear offset: the rear network is fed 10 ms after the front (read from the plug-in in the GUI host)
subprocess.run("sed 's/num_ch >= 6;/(num_ch >= 6 || dbg6);/' tp.jsfx > tpd.jsfx", shell=True)
open("/tmp/tt_cmd.txt", "w").write("var dbg6 1\nslider 135 1\ntimeaudio 8\nprint qRD\nprint LINEMAXB\nprint LINEMAX\nvmem flenB 0 8\nvmem flen 0 8\n")
o = subprocess.run(["./render0", "tpd.jsfx", "320", "200", "/tmp/tt_cmd.txt"], capture_output=True, text=True).stdout
import re
qrd = re.search(r"qRD = (\d+)", o); lb = re.search(r"LINEMAXB = (\d+)", o); lm = re.search(r"LINEMAX = (\d+)", o)
fB = [float(v) for v in re.search(r"flenB\[0..\]: ([^\n]*)", o).group(1).split()]; fA = [float(v) for v in re.search(r"flen\[0..\]: ([^\n]*)", o).group(1).split()]
chk("rear network: fed 10 ms after the front, full line length at 48 kHz, eight lengths of its own (none equal to a front line)", qrd and int(qrd.group(1)) == 480 and lb and lm and lb.group(1) == lm.group(1) and len(set(fB) & set(fA)) == 0 and min(fB) > 0, o.replace("\n", " | ")[:200])
# ITU downmix (L + 0.707 C + 0.707 Ls) against the stereo tail: third-octave spectrum, no notch deeper than 6 dB (uncorrelated channels add in power)
dm = T[:, 0] + 0.7071 * T[:, 2] + 0.7071 * T[:, 4]; st = y2[t0:t1, 0].astype(np.float64)
def bands(v):
    F = np.abs(np.fft.rfft(v * np.hanning(len(v)))) ** 2; f = np.fft.rfftfreq(len(v), 1 / sr); out = []
    fc = 100.0
    while fc < 8000: m = (f >= fc / 1.122) & (f < fc * 1.122); out.append(10 * np.log10(F[m].mean() + 1e-30)); fc *= 1.26
    return np.array(out)
d = bands(dm) - bands(st); d -= np.median(d)
chk("ITU downmix of the 5.1 tail: no comb filter against the Stereo tail (third octaves 100 Hz ... 8 kHz within 6 dB of the median)", np.abs(d).max() < 6, "max deviation %.1f dB" % np.abs(d).max())
chk("nothing non-finite", np.isfinite(y).all())
print("TAILTEST PASS" if all(res) else "TAILTEST FAIL")
