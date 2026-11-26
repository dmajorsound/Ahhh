# UX CHECK (0.314): every control (knob, slider bar, chip, power button, dropdown) must lie inside its module card, and no
# two controls may overlap - in every view and at many window sizes. Instrumented copy of the plugin: card() records its
# box, each control reports its rectangle (page units); offenders are written to memory and read back.
import subprocess, sys, re, os, itertools
src = sys.argv[1] if len(sys.argv) > 1 else "/home/claude/ms/roomservice.jsfx"
subprocess.run(["./mkv.sh", src, "ux.jsfx"], check=True, capture_output=True)
s = open("ux.jsfx").read()
UX = r'''
function uxc(kind, x, y, w, h) local(b, i, o, q, yo, ho) (
  uxOn && crdOn && x > -9000 ? (
    o = x < crdX - 1 || y < crdY - 1 || x + w > crdX + crdW + 1 || y + h > crdY + crdH + 1;
    szoom && !tabm && (gox + (x + w) * gs > gfx_w + 1 || goy + (y + h) * gs > gfx_h + 1 || gox + x * gs < -1) ? o = 1;   // 0.334: a zoom window - inside the plug-in window too
    // overlap with an earlier control of the same card (rectangles shrunk by 1)
    yo = kind == 4 ? y + 11 : y; ho = kind == 4 ? 7 : h;   // a slider bar: its label row may hold a chip (auto)
    q = -1; i = 0; loop(uxR, b = uxRB + i * 5; b[4] == crdN && x + 1 < b[0] + b[2] - 1 && b[0] + 1 < x + w - 1 && yo + 1 < b[1] + b[3] - 1 && b[1] + 1 < yo + ho - 1 ? q = i; i += 1; );
    (o || q >= 0) && uxN < 60 ? ( b = uxB + uxN * 12; b[0] = kind; b[1] = x; b[2] = y; b[3] = w; b[4] = h; b[5] = crdX; b[6] = crdY; b[7] = crdW; b[8] = crdH; b[9] = o; b[10] = q >= 0 ? uxRK[q] : -1; b[11] = crdN; uxN += 1; );
    uxR < 400 ? ( b = uxRB + uxR * 5; b[0] = x; b[1] = yo; b[2] = w; b[3] = ho; b[4] = crdN; uxRK[uxR] = kind; uxR += 1; );
  );
);
'''
# definitions before card()
s = s.replace("function card(x, y, w, h) (", UX + "function card(x, y, w, h) ( crdH = h; crdOn = 1; crdN += 1;", 1)
s = s.replace("gfx_clear = -1;                          // never auto-clear",
  "tb_set ? ( vopt[11] = tb_basic; vopt[3] = 0; vopt[4] = tb_dark; tb_v12 > 0 ? vopt[12] = tb_v12 - 1; tb_set = 0; );\ntb_vi > 0 ? ( vopt[tb_vi] = tb_vv; tb_vi = 0; );\ntb_vj > 0 ? ( vopt[tb_vj] = tb_vw; tb_vj = 0; );\ngfx_clear = -1;   // never auto-clear", 1)
def inj(fn, call):
    global s
    m = re.search(r"function " + fn + r"\([^)]*\)( local\([^)]*\))?\s*\(", s); assert m, fn
    s = s[:m.end()] + " " + call + " " + s[m.end():]
inj("chip", "uxc(1, x, y, w, h);")
inj("tgl", "uxc(2, x + 8, y, 14, 14);")
inj("knob", "uxc(3, cx - KR - 2, cy - KR - 2, 2 * KR + 4, 2 * KR + 4 + 12 * KNS);")
inj("dirknob", "uxc(3, cx - KR - 2, cy - KR - 2, 2 * KR + 4, 2 * KR + 4 + 12 * KNS);")
inj("hsl", "uxc(4, x, y - 6, w, 19);")
inj("ddbox", "uxc(5, x, y, w, h);")
# overlays are not part of a card: menus (mtx), the room view, the top bar / strip
s = s.replace("function mtx(ax, ay, k) (", "function mtx(ax, ay, k) ( crdOn = 0;", 1)
s = s.replace("function gfxp1()\n(", "function gfxp1()\n( crdOn = 0;", 1)
s = re.sub(r"^(@gfx[^\n]*\n)", lambda m: m.group(1) + "uxB = 7000000; uxRB = 7010000; uxRK = 7020000; uxN = 0; uxR = 0; crdOn = 0; crdN = 0; uxOn = 1;\n", s, count=1, flags=re.M)
s = s.replace("dofull ? ( lastukey = ukey; fullcnt = 15; )", "dofull = 1; dofull ? ( lastukey = ukey; fullcnt = 15; )", 1)
open("ux.jsfx", "w").write(s)
KIND = {1: "chip", 2: "power", 3: "knob", 4: "slider bar", 5: "dropdown"}
views = [("Basic", "var tb_basic 1"), ("Expert All", "var tb_basic 0\nvar tb_vi 45\nvar tb_vv 1")]
views += [("Fit all", "var tb_basic 0\nvar tb_vi 45\nvar tb_vv 1\nvar tb_vj 42\nvar tb_vw 1")]
views += [("Basic zoom %d" % z, "var tb_basic 1\nvar szoom %d" % z) for z in (1, 3, 5, 7)]
views += [("Expert zoom %d" % z, "var tb_basic 0\nvar tb_vi 45\nvar tb_vv 1\nvar szoom %d" % z) for z in (1, 3, 4, 5, 6, 7, 10, 14)]
views += [("Tab %d" % t, "var tb_basic 0\nvar tb_vi 46\nvar tb_vv %d" % t) for t in (1, 3, 4, 5, 6, 7, 10, 14)]
sizes = [(760, 574), (900, 650), (1000, 800), (1100, 900), (1280, 720), (1400, 1000), (1920, 1080), (760, 1000), (1600, 600)]
bad = {}
for (vn, vs), (W, H), dark in itertools.product(views, sizes, (0,)):
    sc = "var tb_set 1\nvar tb_v12 1\nvar tb_dark %d\n%s\nslider 40 3\n%snoise 3 0 /tmp/x.raw\nframe\nframe\nframe\nprint uxN\nprint scmax\nvmem uxB 0 720\n" % (dark, vs, os.environ.get("UXPRE", "").replace(";", "\n") + ("\n" if os.environ.get("UXPRE") else ""))   # UXPRE="slider 135 1;slider 136 1": extra setup lines
    open("/tmp/ux.txt", "w").write(sc)
    r = subprocess.run(["./render0", "ux.jsfx", str(W), str(H), "/tmp/ux.txt"], capture_output=True, text=True).stdout
    n = int(float(re.search(r"uxN = ([-\d.e+]+)", r).group(1)))
    scm = float(re.search(r"scmax = ([-\d.e+naif]+)", r).group(1))
    if vn == "Fit all" and scm > 1: bad.setdefault((vn, "page", "does not fit the window (scrolls)"), []).append("%dx%d scrolls %.0f" % (W, H, scm))
    if n:
        v = [float(a) for a in re.search(r"uxB\[0\.\.\]:(.*)", r).group(1).split()]
        for i in range(min(n, 60)):
            b = v[i * 12:(i + 1) * 12]
            what = "%s at (%.0f, %.0f, %.0f x %.0f)" % (KIND.get(int(b[0]), "?"), b[1], b[2], b[3], b[4])
            why = ("outside its card (%.0f, %.0f, %.0f x %.0f)" % (b[5], b[6], b[7], b[8])) if b[9] else ("overlaps a %s" % KIND.get(int(b[10]), "?"))
            key = (vn, what.split(" at")[0], why.split(" (")[0])
            bad.setdefault(key, []).append("%dx%d %s %s" % (W, H, what, why))
for k, v in sorted(bad.items()):
    print("UX %s: %s %s  [%d sizes] e.g. %s" % (k[0], k[1], k[2], len(v), v[0]))
print("UXCOUNT", len(bad))
