# roomservice pro, Beta 7: loudspeaker list. The ring sits on the listener and turns with his facing; ring in the room = the
# listener held in the middle; ITU angles adjustable; Film with fixed cinema angles and surround arrays
import subprocess, re, sys, numpy as np
jsfx = sys.argv[1]; res = []
def chk(n, ok, i=""): res.append(ok); print(("PASS " if ok else "FAIL ") + n + ("  - " + i if i else ""))
def geo(sl, extra=""):
    subprocess.run(["./mkv.sh", jsfx, "tg.jsfx"], check=True)
    open("/tmp/tg.txt", "w").write("".join("slider %d %g\n" % s for s in sl) + "audio 4 0.1\nvmem SPKL 0 64\n" + extra)
    o = subprocess.run(["./render0", "tg.jsfx", "320", "200", "/tmp/tg.txt"], capture_output=True, text=True).stdout
    v = [float(t) for t in o.split("SPKL[0..]:")[1].split("\n")[0].split()]
    return np.array(v[:48]).reshape(6, 8), v[60:64], o
d, c, _ = geo([(135, 1)]); W, D = 5.5, 4.5; lx, ly = 2.75, 2.25; R = min(W, D) * 0.3
chk("ITU default: L / R at -30 / +30 deg, C at 0, Ls / Rs at -110 / +110 deg", np.allclose(d[[0, 1, 2, 4, 5], 3], [-30, 30, 0, -110, 110], atol=0.01), str(d[:, 3].round(2)))
chk("the ring is centered on the listener (default: the middle of the room)", np.allclose(c[:2], [lx, ly]) and np.allclose(c[2], R), str(c))
dist = np.hypot(d[[0, 1, 2, 4, 5], 0] - lx, d[[0, 1, 2, 4, 5], 1] - ly)
chk("all five speakers the same distance from the listener", np.allclose(dist, R, atol=1e-6), str(dist.round(3)))
chk("default height 1.2 m for all speakers", np.allclose(d[:, 2], 1.2))
l, cl, _ = geo([(135, 1), (12, 4.0), (13, 1.0)])
chk("ring follows the listener: moved to (4, 1), the ring's center and every speaker move with him, the angles stay", np.allclose(cl[:2], [4.0, 1.0]) and np.allclose(l[[0, 1, 2, 4, 5], :2] - d[[0, 1, 2, 4, 5], :2], [[1.25, -1.25]] * 5) and np.allclose(l[:, 3], d[:, 3]), str(cl))
t, ct, _ = geo([(135, 1), (15, 1), (16, 90)])   # facing fixed, 90 degrees = towards the right wall
chk("the ring turns with the listener's facing: facing the right wall, C stands to the right of the listener", np.allclose(t[2, :2], [lx + R, ly], atol=1e-3) and np.allclose(ct[3], np.pi / 2, atol=1e-6), str(t[2, :2]) + " turn %.3f" % ct[3])
r, cr, o = geo([(135, 1), (144, 1), (12, 4.0), (13, 1.0), (15, 1), (16, 90)], "getslider 12\ngetslider 13\ngetslider 15\ngetslider 16\n")
chk("ring in the room: the listener is held in the middle, facing the screen wall - whatever his sliders said", np.allclose(cr[:2], [lx, ly]) and abs(cr[3]) < 1e-6 and "slider12 = 2.75" in o and "slider13 = 2.25" in o and "slider15 = 1" in o and "slider16 = 0" in o, " ".join(l for l in o.split("\n") if l.startswith("slider")))
w, cw, _ = geo([(135, 1), (1, 8.0), (2, 6.0)])
chk("a bigger room: a bigger ring (30 % of the smaller side), centered on the listener", np.allclose(cw[2], 1.8) and np.allclose(cw[:2], [2.75, 2.25]), str(cw))
s2, cs, _ = geo([(135, 1), (30, 2.0)])
chk("the Size factor scales the ring and the listener's place with the room", np.allclose(cs[2], min(W, D) * 2 * 0.3) and np.allclose(cs[:2], [W, D]), str(cs))
a, _, _ = geo([(135, 1), (137, 40), (138, 130)])
chk("ITU angles are adjustable (front 40, surround 130)", np.allclose(a[[0, 1, 4, 5], 3], [-40, 40, -130, 130], atol=0.01))
h, _, _ = geo([(135, 1), (139, 2.0)])
chk("speaker height is one fixed value for all speakers", np.allclose(h[:, 2], 2.0))
lo, _, _ = geo([(135, 1), (3, 2.0), (139, 3.0)])
chk("height is limited below the ceiling (room height 2.0 m)", lo[:, 2].max() <= 1.9 + 1e-9, str(lo[0, 2]))
f, cf, _ = geo([(135, 1), (136, 1)])
chk("Film: the cinema seen from the mixing position - L / R at -25 / +25, C 0, the surround arrays centered at -100 / +100 deg", np.allclose(f[[0, 1, 2, 4, 5], 3], [-25, 25, 0, -100, 100]) and np.allclose(f[[4, 5], 4], 1) and np.allclose(f[[0, 1, 2], 4], 0), str(f[:, 3]))
print("GEOTEST PASS" if all(res) else "GEOTEST FAIL")
