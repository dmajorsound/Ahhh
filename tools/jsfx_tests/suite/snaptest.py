# snapshots, morph, undo: save two slots, load them back, morph half way, and make sure undo never touches the slots
import subprocess, sys, re
src = sys.argv[1]
s = open(src).read()
s = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', s)
anchor = 'gfx_clear = -1;                          // never auto-clear'
assert anchor in s
s = s.replace(anchor, 'tb_save > 0 ? ( saveslot(tb_save - 1); tb_save = 0; ); tb_load > 0 ? ( loadslot(tb_load - 1); tb_load = 0; );\n' + anchor, 1)
open('/tmp/snap_t.jsfx', 'w').write(s)
# slider numbers (1-based) and values for snapshot A / B: room width, decay-ish, delay time (ext. slot), call line, width
A = {2: 6.0, 70: 120.0, 98: 80.0, 112: 30.0, 37: 25.0, 35: 3}
B = {2: 10.0, 70: 320.0, 98: 160.0, 112: 70.0, 37: 75.0, 35: 3}
def sl(d): return "".join("slider %d %g\n" % (k - 1, v) for k, v in d.items())
def gets(keys): return "".join("getslider %d\n" % (k - 1) for k in keys)
keys = sorted(A)
cmd = "audio 2 0\nframe\n" + sl(A) + "frame\nvar tb_save 1\nframe\n" + sl(B) + "frame\nvar tb_save 2\nframe\n"
# change things, let the undo base commit (> 0.4 s), the slots must stay
cmd += "slider 1 4\nslider 69 50\nframe\nsleep 600\nframe\nframe\n"
cmd += "var tb_load 1\nframe\naudio 2 0\n" + gets(keys) + "print SEP1\n"
cmd += "var tb_load 2\nframe\naudio 2 0\n" + gets(keys) + "print SEP2\n"
cmd += "slider 63 1.5\naudio 4 0\n" + gets(keys) + "print SEP3\n"
open('/tmp/snap.txt', 'w').write(cmd)
r = subprocess.run(['./render0', '/tmp/snap_t.jsfx', '760', '574', '/tmp/snap.txt'], capture_output=True, text=True).stdout
vals = [float(m) for m in re.findall(r'slider\d+ = ([-0-9.e+]+)', r)]
n = len(keys); la, lb, mo = vals[:n], vals[n:2 * n], vals[2 * n:3 * n]
ok = True
for i, k in enumerate(keys):
    ea, eb = A[k], B[k]
    em = (ea + eb) / 2 if k not in (35,) else ea
    fa = abs(la[i] - ea) < 1e-6; fb = abs(lb[i] - eb) < 1e-6
    # morph: linear or log for some sliders - accept anything between A and B (strictly inside for continuous ones)
    fm = (min(ea, eb) - 1e-6 <= mo[i] <= max(ea, eb) + 1e-6) and (k == 35 or (min(ea, eb) < mo[i] < max(ea, eb)))
    ok &= fa and fb and fm
    print("slider%-4d A %8.3f (load %8.3f)  B %8.3f (load %8.3f)  morph 1.5 -> %8.3f  %s" % (k, ea, la[i], eb, lb[i], mo[i], "ok" if fa and fb and fm else "FAIL"))
print("SNAPSHOT/MORPH/UNDO", "PASS" if ok else "FAIL")
