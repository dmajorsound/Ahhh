# roomservice pro, Beta 1: the Stereo path must stay identical to the 1.0; channel handling of the 6-channel pins; geometry
import numpy as np, subprocess, sys, os
BASE, PRO = sys.argv[1], sys.argv[2]
rng = np.random.default_rng(5); n = 48000 * 2 // 256 * 256
def run(jsfx, nch, x, sl=()):
    subprocess.run(["./mkv.sh", jsfx, "tp.jsfx"], check=True)
    x.astype(np.float32).tofile("/tmp/tp_in.raw"); subprocess.run(["rm", "-f", "/tmp/tp_out.raw"])
    subprocess.run(["./render6", "tp.jsfx", str(nch), "/tmp/tp_in.raw", "/tmp/tp_out.raw"] + ["%d=%g" % s for s in sl], capture_output=True)
    return np.fromfile("/tmp/tp_out.raw", dtype=np.float32).reshape(-1, nch)
res = []
def chk(name, ok, info=""): res.append(ok); print(("PASS " if ok else "FAIL ") + name + ("  - " + info if info else ""))
x2 = (rng.standard_normal((n, 2)) * 0.1)
# room on, motion-free defaults; plus a second setting with source model + delay + barrier so more of the path is live
cases = {"defaults": [], "busy": [(34, 3), (40, 1), (23, 2.2), (44, 20)]}   # 0-based slider indices
for nm, sl in cases.items():
    a = run(BASE, 2, x2, sl); b = run(PRO, 2, x2, sl)
    chk("2-ch track, Stereo: bit-identical to the 1.0 (%s)" % nm, a.shape == b.shape and np.array_equal(a, b), "max diff %.3g" % np.abs(a - b).max())
    b2 = run(PRO, 2, x2, sl + [(135, 1)])
    chk("2-ch track, Output 5.1 selected: stays stereo, identical to the 1.0 (%s)" % nm, np.array_equal(a, b2))
x6 = np.concatenate([x2, rng.standard_normal((n, 4)) * 0.1], 1)
a = run(BASE, 2, x2); s6 = run(PRO, 6, x6)
chk("6-ch track, Stereo: channels 1/2 identical to the 1.0", np.array_equal(a, s6[:, :2]))
chk("6-ch track, Stereo: channels 3-6 pass through untouched", np.array_equal(s6[:, 2:], x6[:, 2:].astype(np.float32)))
f6 = run(PRO, 6, x6, [(135, 1)])
pw = lambda v: 10 * np.log10(np.mean(v.astype(np.float64) ** 2, 0) + 1e-30)
chk("6-ch track, 5.1: L / R are rendered for loudspeakers (no longer the binaural stereo result)", not np.array_equal(a, f6[:, :2]))
chk("6-ch track, 5.1: C, Ls, Rs and the LFE carry signal", np.abs(f6[:, 2]).max() > 1e-4 and np.abs(f6[:, 4:]).max() > 1e-4 and np.abs(f6[:, 3]).max() > 1e-4, "levels dB " + " ".join("%.1f" % v for v in pw(f6)))
chk("6-ch track, 5.1: the total power of the five loudspeakers stays within 3 dB of the stereo pair", abs(10 * np.log10(np.sum(f6.astype(np.float64) ** 2) / max(1e-30, np.sum(a.astype(np.float64) ** 2)))) < 3, "%.2f dB" % (10 * np.log10(np.sum(f6.astype(np.float64) ** 2) / np.sum(a.astype(np.float64) ** 2))))
chk("6-ch track, 5.1: nothing non-finite", np.isfinite(f6).all())
# silence: the plug-in goes to sleep, 5.1 must not leave the old channel 3-6 input on the output
z = np.zeros((n, 6), np.float32); z[: n // 2, :] = x6[: n // 2]; z[n // 2:, :2] = 0; z[n // 2:, 2:] = x6[n // 2:, 2:]
q = run(PRO, 6, z, [(135, 1), (35, 1)])   # room engine off
chk("6-ch track, 5.1, silent channels 1/2: channels 3-6 stay silent (also when the plug-in sleeps)", np.abs(q[:, 2:]).max() == 0)
print("PROTEST PASS" if all(res) else "PROTEST FAIL")
