#!/bin/bash
# null test: every case through ysfx (original JSFX) and the native port. Stereo cases (cases/, 2 channels) and
# 5.1 cases (cases51/, 6 interleaved channels: NCH=6). The reference needs the 1-argument slider_automate (mkv.sh).
cd "$(dirname "$0")"; SR=${SR:-48000}; BS=${BS:-256}; mkdir -p out
sh ../tools/jsfx_tests/mkv.sh ../jsfx/Ahh.jsfx out/ref.jsfx
run_set() { # $1 = case dir, $2 = channels, $3 = input
  for c in $1/*.txt; do n=$(basename $c .txt)
    NCH=$2 ../build_cli/refrender out/ref.jsfx $c $3 out/ref_$2_$n.f64 $SR $BS &
    NCH=$2 ../build_cli/natrender $c $3 out/nat_$2_$n.f64 $SR $BS &
  done; wait
}
run_set cases 2 ${IN:-in.f64}
run_set cases51 6 ${IN6:-in6.f64}
python3 - <<'PY'
import numpy as np, glob, os
bad = 0
for f in sorted(glob.glob('out/ref_*.f64')):
    n = os.path.basename(f)[4:-4]; a = np.fromfile(f); b = np.fromfile('out/nat_%s.f64' % n)
    d = np.abs(a - b); same = (a == b).mean(); peak = np.abs(a).max()
    st = 'BITGLEICH' if d.max() == 0 else 'ABWEICHUNG'
    if d.max() != 0: bad += 1
    fi = int(np.argmax(d > 0)) // (6 if n.startswith('6_') else 2) if d.max() > 0 else -1
    print('%-22s %-10s peak %.4f  maxdiff %.3g  gleich %.4f  erste %d' % (n, st, peak, d.max(), same, fi))
print('FAIL', bad)
PY
