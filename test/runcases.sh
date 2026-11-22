#!/bin/bash
# null test: every case through ysfx (original JSFX) and the native port
cd "$(dirname "$0")"; IN=${IN:-in.f64}; SR=${SR:-48000}; BS=${BS:-256}
for c in cases/*.txt; do n=$(basename $c .txt)
  ./refrender /home/claude/port/jsfx/roomservice.jsfx $c $IN out/ref_$n.f64 $SR $BS &
  ../build_cli/natrender $c $IN out/nat_$n.f64 $SR $BS &
done; wait
python3 - <<'PY'
import numpy as np, glob, os
bad = 0
for f in sorted(glob.glob('out/ref_*.f64')):
    n = os.path.basename(f)[4:-4]; a = np.fromfile(f); b = np.fromfile('out/nat_%s.f64' % n)
    d = np.abs(a - b); same = (a == b).mean(); peak = np.abs(a).max()
    st = 'BITGLEICH' if d.max() == 0 else 'ABWEICHUNG'
    if d.max() != 0: bad += 1
    fi = int(np.argmax(d > 0)) // 2 if d.max() > 0 else -1
    print('%-16s %-10s peak %.4f  maxdiff %.3g  gleich %.4f  erste %d' % (n, st, peak, d.max(), same, fi))
print('FAIL', bad)
PY
