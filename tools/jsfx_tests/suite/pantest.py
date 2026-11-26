# roomservice pro, Beta 5: the 5.1 panning of the direct sound (free field, no ground: the direct sound alone)
import numpy as np, subprocess, sys
PRO = sys.argv[1]
rng = np.random.default_rng(7); n = 48000 * 2 // 256 * 256
def run(nch, x, sl=()):
    subprocess.run(["./mkv.sh", PRO, "tp.jsfx"], check=True)
    x.astype(np.float32).tofile("/tmp/tp_in.raw"); subprocess.run(["rm", "-f", "/tmp/tp_out.raw"])
    subprocess.run(["./render6", "tp.jsfx", str(nch), "/tmp/tp_in.raw", "/tmp/tp_out.raw"] + ["%d=%g" % s for s in sl], capture_output=True)
    return np.fromfile("/tmp/tp_out.raw", dtype=np.float32).reshape(-1, nch)
res = []
def chk(name, ok, info=""): res.append(ok); print(("PASS " if ok else "FAIL ") + name + ("  - " + info if info else ""))
x = np.zeros((n, 6), np.float32); x[:, 0] = rng.standard_normal(n) * 0.1; x[:, 1] = x[:, 0]   # a mono source (a stereo input keeps its width on L / R, as in 1.0)
LX, LY = 2.75, 2.25
base = [(135, 1), (0, 1), (118, 0), (15, 1), (16, 0), (12, LX), (13, LY), (14, 1.5), (11, 1.5), (137, 30), (138, 110)]   # 5.1, free field, no ground, facing fixed = top wall
def lev(sl):
    y = run(6, x, base + sl)[n // 2:]   # second half: everything settled
    y2 = run(2, x[:, :2], base + sl)[n // 2:]   # the same position in stereo: the same power in total
    return 10 * np.log10(np.mean(y.astype(np.float64) ** 2, 0) + 1e-30), y, 10 * np.log10(np.sum(y2.astype(np.float64) ** 2) / len(y2) + 1e-30)
def src(az, r=2.0): a = np.radians(az); return [(9, LX + np.sin(a) * r), (10, LY - np.cos(a) * r)]
names = "L R C LFE Ls Rs".split()
fmt = lambda l: " ".join("%s %.1f" % (nm, v) for nm, v in zip(names, l))
l0, y0, t0 = lev(src(0) + [(143, 100)]); chk("source ahead, discrete center: C alone (the LFE carries its bass share)", l0[2] > max(l0[0], l0[1], l0[4], l0[5]) + 30 and l0[3] < l0[2] - 15, fmt(l0))
l1, _, t1 = lev(src(0) + [(143, 0)]); chk("source ahead, phantom center: L = R, no C", abs(l1[0] - l1[1]) < 0.3 and l1[2] < l1[0] - 30 and l1[4] < l1[0] - 30, fmt(l1))
chk("phantom and discrete center: the same power", abs(10 * np.log10(np.sum(10 ** (l1[[0, 1, 2, 4, 5]] / 10))) - 10 * np.log10(np.sum(10 ** (l0[[0, 1, 2, 4, 5]] / 10)))) < 0.3)
l2, _, t2 = lev(src(-30)); chk("source at -30 degrees: L alone", l2[0] > max(l2[1], l2[2], l2[4], l2[5]) + 30, fmt(l2))
l3, _, t3 = lev(src(30)); chk("source at +30 degrees: R alone", l3[1] > max(l3[0], l3[2], l3[4], l3[5]) + 30, fmt(l3))
l4, _, t4 = lev(src(110)); chk("source at +110 degrees: Rs alone", l4[5] > max(l4[0], l4[1], l4[2], l4[4]) + 30, fmt(l4))
l5, _, t5 = lev(src(70)); chk("source at +70 degrees: R and Rs share it, nothing on the left", l5[1] > -40 and l5[5] > -40 and abs(l5[1] - l5[5]) < 1 and l5[0] < l5[1] - 30 and l5[4] < l5[5] - 30, fmt(l5))
l6, _, t6 = lev(src(180)); chk("source behind: Ls = Rs, nothing in front", abs(l6[4] - l6[5]) < 0.3 and l6[0] < l6[4] - 30 and l6[2] < l6[4] - 30, fmt(l6))
l7, _, t7 = lev(src(-30) + [(9, LX - np.sin(np.radians(30)) * 2.5), (10, LY - np.cos(np.radians(30)) * 2.5)]); chk("farther away: quieter, still on L", l7[0] < l2[0] - 1 and l7[0] > max(l7[1], l7[5]) + 30, fmt(l7))
tot = [10 * np.log10(np.sum(10 ** (l[[0, 1, 2, 4, 5]] / 10))) - t for l, t in ((l0, t0), (l1, t1), (l2, t2), (l3, t3), (l4, t4), (l5, t5), (l6, t6), (l7, t7))]
chk("every direction: the five loudspeakers carry the power the stereo pair carries (within 0.5 dB)", max(abs(t) for t in tot) < 0.5, " ".join("%.2f" % t for t in tot))
l8, _, t8 = lev(src(-30) + [(136, 1)]); chk("Film layout: a source at -30 degrees still sits on L", l8[0] > max(l8[1], l8[2], l8[4], l8[5]) + 12, fmt(l8))
l9, y9, t9 = lev(src(0, 0) + [(11, 1.5 + 2)]); chk("source overhead: spread over all five (no channel more than 3 dB above another)", max(l9[[0, 1, 2, 4, 5]]) - min(l9[[0, 1, 2, 4, 5]]) < 3, fmt(l9))
chk("nothing non-finite", all(np.isfinite(v).all() for v in (y0, y9)))
# snap to loudspeaker (slider146): the direct sound on the nearest loudspeaker alone; phantom center still L = R; hysteresis
ls, _, _ = lev(src(50) + [(145, 1), (143, 100)]); chk("snap: source at +50 degrees sits on R alone", ls[1] > max(ls[0], ls[2], ls[4], ls[5]) + 40, fmt(ls))
ls2, _, _ = lev(src(75) + [(145, 1), (143, 100)]); chk("snap: source at +75 degrees sits on Rs alone", ls2[5] > max(ls2[0], ls2[1], ls2[2], ls2[4]) + 40, fmt(ls2))
ls3, _, _ = lev(src(12) + [(145, 1), (143, 0)]); chk("snap with phantom center: source at +12 degrees -> C -> L = R, no C", abs(ls3[0] - ls3[1]) < 0.3 and ls3[2] < ls3[0] - 40 and ls3[5] < ls3[0] - 40, fmt(ls3))
lp, _, _ = lev(src(50) + [(143, 100)]); chk("snap keeps the power of the panned source (same position, +50 degrees)", abs(10 * np.log10(np.sum(10 ** (ls[[0, 1, 2, 4, 5]] / 10))) - 10 * np.log10(np.sum(10 ** (lp[[0, 1, 2, 4, 5]] / 10)))) < 0.3, "snap %.2f  panned %.2f" % (10 * np.log10(np.sum(10 ** (ls[[0, 1, 2, 4, 5]] / 10))), 10 * np.log10(np.sum(10 ** (lp[[0, 1, 2, 4, 5]] / 10)))))
# with the room on: the reflections still reach the other loudspeakers (snap moves only the direct sound)
yr = run(6, x, [(135, 1), (145, 1), (143, 100)] + src(50))[n // 2:]; lr = 10 * np.log10(np.mean(yr.astype(np.float64) ** 2, 0) + 1e-30)
chk("snap in the room: R carries the direct sound, the other loudspeakers still carry reflections and reverb (within 25 dB)", lr[1] == max(lr) and min(lr[[0, 2, 4, 5]]) > lr[1] - 25, fmt(lr))
# motion in 5.1 (circle with Doppler x 4, pass-by): finite, every loudspeaker alive, no level bursts (50 ms windows)
xm = np.zeros((48000 * 3 // 256 * 256, 6), np.float32); xm[:, 0] = rng.standard_normal(len(xm)) * 0.1; xm[:, 1] = xm[:, 0]
for nm, sl in {"circle + Doppler x 4": [(135, 1), (99, 1), (102, 0.5), (117, 4)], "pass-by": [(135, 1), (99, 1), (101, 4), (102, 0.3)]}.items():
    y = run(6, xm, sl)[len(xm) // 3:]; y = y[:len(y) // 2400 * 2400]
    lv = 10 * np.log10(np.mean(y.astype(np.float64) ** 2, 0) + 1e-30); e = 10 * np.log10(np.mean(y.reshape(-1, 2400, 6).astype(np.float64) ** 2, 1) + 1e-12); jump = np.abs(np.diff(e, axis=0)).max()
    chk("motion %s: finite, all five loudspeakers alive, no 50 ms level step above 8 dB" % nm, np.isfinite(y).all() and min(lv[[0, 1, 2, 4, 5]]) > -45 and jump < 8, fmt(lv) + " step %.1f dB" % jump)
print("PANTEST PASS" if all(res) else "PANTEST FAIL")
