# 0.362: project state: the view options (incl. the reflectors, vopt 52 ...) and the snapshots survive save + load; the count written is the count in the header
import subprocess, sys, re
s = open(sys.argv[1]).read()
s = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', s)
anchor = 'gfx_clear = -1;                          // never auto-clear'
assert anchor in s
s = s.replace(anchor, 'tb_save > 0 ? ( saveslot(tb_save - 1); tb_save = 0; );\ntb_w > 0 ? ( vopt[53] = tb_w; vopt[61] = tb_w * 2; tb_w = 0; );\ntb_o53 = vopt[53]; tb_o61 = vopt[61]; tb_u0 = uslot[0]; tb_s2 = slider2;\n' + anchor, 1)
open('/tmp/ser_t.jsfx', 'w').write(s)
cmd = "audio 2 0\nslider 1 9.5\nvar tb_w 7.5\nframe\nvar tb_save 1\nframe\nframe\nwritestate /tmp/ser_state.bin\nslider 1 3\nvar tb_w 1\nframe\nframe\nreadstate /tmp/ser_state.bin\nframe\nframe\nprint tb_o53\nprint tb_o61\nprint tb_u0\nprint tb_s2\n"
open('/tmp/ser.txt', 'w').write(cmd)
r = subprocess.run(['./render0', '/tmp/ser_t.jsfx', '760', '574', '/tmp/ser.txt'], capture_output=True, text=True).stdout
v = [float(x) for k, x in re.findall(r"(tb_\w+) = ([-0-9.e]+)", r)]
ok = len(v) == 4 and abs(v[0] - 7.5) < 1e-6 and abs(v[1] - 15) < 1e-6 and v[2] != 0 and abs(v[3] - 9.5) < 1e-6
print("SERIAL PASS" if ok else "SERIAL FAIL %s %s" % (v, r[-300:]))
