# 0.377: 8 settle frames (was 6) - an opening fade ends at frame 7 (one pixel, one step of brightness), that is no flicker
import subprocess, numpy as np, sys
from PIL import Image
def ppm(f): return np.asarray(Image.open(f)).astype(int)
modes = {'all_fit': "var tb_vi 45\nvar tb_vv 1\nvar tb_vj 42\nvar tb_vw 1\n", 'all': "var tb_vi 45\nvar tb_vv 1\n",
         'tab3': "var tb_vi 46\nvar tb_vv 3\n", 'tab7': "var tb_vi 46\nvar tb_vv 7\n", 'basic_fit': "var tb_vi 36\nvar tb_vv 1\n"}
sizes = [(int(a), int(b)) for a, b in (x.split('x') for x in sys.argv[1:])] or [(1500, 880), (1650, 1000), (1100, 900), (760, 574), (1400, 1000)]
for m, mc in modes.items():
    for W, H in sizes:
        basic = 1 if m.startswith('basic') else 0
        sc = f"var tb_set 1\nvar tb_basic {basic}\nvar tb_v12 1\n" + mc + "audio 4 0\n" + "mouse 3 300 0\nframe\nmouse 4 300 0\nframe\n" * 4 + "save /tmp/fa.ppm\nmouse 3 301 0\nframe\nsave /tmp/fb.ppm\nmouse 4 302 0\nframe\nsave /tmp/fc.ppm\n"
        open('/tmp/fd.txt', 'w').write(sc)
        subprocess.run(['./render0', 't3.jsfx', str(W), str(H), '/tmp/fd.txt'], capture_output=True)
        a, b, c = ppm('/tmp/fa.ppm'), ppm('/tmp/fb.ppm'), ppm('/tmp/fc.ppm')
        d1 = (np.abs(a - b).sum(2) > 0).sum(); d2 = (np.abs(b - c).sum(2) > 0).sum()
        print(f"{m:10s} {W}x{H}: changed pixels frame→frame {d1}, {d2}")
