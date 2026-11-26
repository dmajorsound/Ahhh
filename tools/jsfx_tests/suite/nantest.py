# NaN / Inf safety: a burst of NaN at the input and a NaN inside the signal path must give finite output and the plugin must work again afterwards
import numpy as np, subprocess, sys
src = open(sys.argv[1]).read()
def run(mod, name):
    s = mod(src); open("/tmp/nt.jsfx", "w").write(s)
    subprocess.run("./mkv.sh /tmp/nt.jsfx /tmp/nt2.jsfx", shell=True, capture_output=True)
    n = 48000 * 3; rng = np.random.default_rng(5); L = rng.standard_normal(n) * 0.1
    np.stack([L, L], 1).astype(np.float32).tofile('/tmp/nt.raw')
    open("/tmp/nt.txt", "w").write("audio 8 0\nrawin %d /tmp/nt.raw /tmp/nto.raw\n" % (n // 256 + 4))
    subprocess.run(['rm', '-f', '/tmp/nto.raw']); subprocess.run(['./render0', "/tmp/nt2.jsfx", '320', '200', '/tmp/nt.txt'], capture_output=True)
    y = np.fromfile('/tmp/nto.raw', dtype=np.float32).reshape(-1, 2)
    fin = np.isfinite(y).all(); tail = np.abs(y[-24000:]).max() if fin else -1
    print(name, "finite", fin, "tail peak %.3f" % tail); return fin and tail > 0.01
ok1 = run(lambda s: s.replace("inL = spl0; inR = spl1;\n", "ntc += 1; ntc > 30000 && ntc < 30050 ? spl0 = log(-1); ntc > 31000 && ntc < 31010 ? spl1 = exp(1000);\ninL = spl0; inR = spl1;\n", 1), "input NaN/Inf burst")
ok2 = run(lambda s: s.replace("nanB = !(abs(outL)", "ntc += 1; ntc == 40000 ? outL = log(-1);\nnanB = !(abs(outL)", 1), "NaN in the output stage")
ok3 = run(lambda s: s.replace("slp = 0;\ninL = spl0;", "slp = 0; ntc += 1; ntc == 40000 ? ( memset(dlL + 5, 1/0 - 1/0, 50); ibuf[300] = log(-1); );\ninL = spl0;", 1).replace("slider35:","slider35:",1), "NaN inside the delay / room buffers")
print("NANTEST PASS" if ok1 and ok2 and ok3 else "NANTEST FAIL")
