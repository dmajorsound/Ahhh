# 0.389: "Doppler" chip in the Stage View (slider135): off = dragging the source by hand changes the distance without a pitch
# glide (the direct delay is held); on = the real glide (as before). Measured: a 1 kHz sine while the source moves 1 -> 4 m
import numpy as np, subprocess, sys, os
src = sys.argv[1]
subprocess.run(["./mkv.sh", src, "rs_dph.jsfx"], check=True, capture_output=True)
def run(dop):
    fn = '/tmp/dph.raw'
    if os.path.exists(fn): os.remove(fn)
    sc = "slider 134 %d\nslider 9 2.75\nslider 10 2.0\nslider 12 2.75\nslider 13 3.0\nslider 1 10\nslider 2 10\nslider 0 1\nslider 118 0\nslider 19 0\nslider 20 0\nslider 110 0\nplay 1 0\naudio 60 0\n" % dop   # free field, no ground: the direct sound alone
    sc += "sine 40 1000 0.3 %s\n" % fn
    for k in range(60): sc += "slider 10 %.4f\nsine 1 1000 0.3 %s\n" % (2.0 - k * 0.03, fn)   # the source walks away ~ 1.8 m in 60 blocks (0.32 s): 5.6 m/s
    sc += "sine 40 1000 0.3 %s\n" % fn
    open('/tmp/dph.txt', 'w').write(sc)
    subprocess.run(['./render0', 'rs_dph.jsfx', '300', '200', '/tmp/dph.txt'], capture_output=True, text=True)
    y = np.fromfile(fn, np.float32).reshape(-1, 2).astype(float)[:, 0]
    seg = y[40 * 256 + 2000: 100 * 256]   # while it moves
    z = np.where((seg[:-1] < 0) & (seg[1:] >= 0))[0]
    return 48000 / np.mean(np.diff(z)) if len(z) > 10 else 0
fon, foff = run(0), run(1)
ok = abs(foff - 1000) < 2 and fon < 998
print("DOPHAND PASS  on %.1f Hz  off %.1f Hz" % (fon, foff) if ok else "DOPHAND FAIL  on %.1f Hz  off %.1f Hz" % (fon, foff))
