# NULL TEST: with everything off the plugin must pass the input unchanged (sample-exact).
# room engine off (slider36 = 1), source model off (85 = 0), delay off (65 = 0), filters off, limiter off (23 = 0),
# dry/wet 100, gains 0 dB, width 100 %, mono mix off. An impulse (0.5) must come out as exactly one sample of 0.5.
import numpy as np, subprocess, sys, os
jsfx = sys.argv[1] if len(sys.argv) > 1 else 't.jsfx'
def run(extra, name):
    cfg = ["slider 35 1", "slider 84 0", "slider 64 0", "slider 23 0", "slider 26 0", "slider 22 0", "slider 38 0", "slider 17 0", "slider 39 0", "slider 21 0", "slider 97 100", "slider 109 0"] + extra   # (host slider indices are 0-based)
    open('sc_null.txt', 'w').write("\n".join(cfg) + f"\nnoise 40 0 /tmp/x.raw\nclicks 2400 100000000 0.5 /home/claude/host/{name}.raw\n")
    if os.path.exists(name + '.raw'): os.remove(name + '.raw')
    r = subprocess.run(['./render0', jsfx, '320', '200', 'sc_null.txt'], capture_output=True, text=True)
    a = np.fromfile(name + '.raw', dtype=np.float32).reshape(-1, 2).astype(np.float64)
    return a
ok = 1
for extra, name, want in (([], 'null_st', 'stereo'), (["slider 109 1"], 'null_mono', 'mono mix')):
    a = run(extra, name)
    nz = np.argwhere(np.abs(a) > 0)
    peakL = a[:, 0].max(); peakR = a[:, 1].max()
    others = (np.abs(a) > 0).sum() - 2
    print(f"{want:9s}: nonzero samples L {int((np.abs(a[:,0])>0).sum())} R {int((np.abs(a[:,1])>0).sum())}, peak L {peakL:.9f} R {peakR:.9f}, max |x| beside the impulse {np.sort(np.abs(a).ravel())[-3] if a.size > 2 else 0:.3e}")
    if not (abs(peakL - 0.5) < 1e-7 and abs(peakR - 0.5) < 1e-7 and (np.abs(a[:,0]) > 0).sum() == 1 and (np.abs(a[:,1]) > 0).sum() == 1): ok = 0
print("NULL TEST", "PASS" if ok else "FAIL")
