# 0.364 FREE FIELD PRESETS: entering the free field gives the Street (20 x 30 m, listener in the middle, source 1.5 m in front, facades 4 m high);
# every one of the 17 presets sets area, ground and the two reflectors; the Reset icons of the Free field and Reflectors tabs work
import subprocess, sys, re
src = open(sys.argv[1]).read()
FFP = {}
for n, v in re.findall(r'FFP\[(\d+)\] = ([-0-9.]+);', src):
    FFP[int(n)] = float(v)
s = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', src)
anchor = 'gfx_clear = -1;                          // never auto-clear'
assert anchor in s
probe = ('tb_set ? ( vopt[11] = 0; vopt[40] = 0; tb_set = 0; );\ntb_vi > 0 ? ( vopt[tb_vi] = tb_vv; tb_vi = 0; );\n'
         'tb_a0 = slider2 * slider31; tb_a1 = slider3 * slider31; tb_a2 = slider119; tb_a3 = vopt[52]; tb_a4 = vopt[58]; tb_a5 = vopt[57]; tb_a6 = vopt[63];'
         ' tb_a7 = (slider14 - slider11) * slider31; tb_a8 = slider13 * slider31; tb_a9 = slider1; tb_a10 = slider12; tb_a11 = slider15; tb_a12 = vopt[59]; tb_a13 = slider4; tb_a14 = slider65; tb_a15 = vopt[66]; tb_a16 = vopt[52]; tb_a17 = vopt[58];\n')
open('/tmp/fp_t.jsfx', 'w').write(s.replace(anchor, probe + anchor, 1))
N = 18
def run(cmd):
    open('/tmp/fp.txt', 'w').write("var tb_set 1\nvar tb_basic 0\nframe\nvar tb_vi 46\nvar tb_vv 15\nframe\nframe\n" + cmd + "".join("print tb_a%d\n" % i for i in range(N)))
    r = subprocess.run(['./render0', '/tmp/fp_t.jsfx', '1100', '700', '/tmp/fp.txt'], capture_output=True, text=True).stdout
    d = dict(re.findall(r"(tb_a\d+) = ([-0-9.e]+)", r))
    return [float(d.get('tb_a%d' % i, 'nan')) for i in range(N)]
def click(x, y):
    return "mouse %d %d 0 0\nframe\nmouse %d %d 1 0\nframe\nmouse %d %d 0 0\nframe\nframe\n" % (x, y, x, y, x, y)
enter = click(546, 380)
ok = True; msg = []
v = run(enter)
c0 = abs(v[0] - 20) < 0.01 and abs(v[1] - 30) < 0.01 and v[2] == 1 and v[3] == 1 and v[4] == 1 and v[5] == 4 and v[6] == 4 and abs(v[7] - 1.5) < 0.01 and abs(v[8] - 10) < 0.01 and v[9] == 1
ok &= c0; msg.append(("default", v))
for k in range(17):
    b = [FFP[k * 16 + i] for i in range(16)]
    y = int(98 + k * 17.2)   # (row pitch since 1.0.3: 17.2 px at 1100 x 700)
    v = run(enter + click(245, 410) + click(200, y))
    c = abs(v[0] - b[0]) < 0.05 and abs(v[1] - b[1]) < 0.05 and v[2] == b[3] and v[3] == b[4] and v[4] == b[10] and abs(v[5] - b[9]) < 0.01 and abs(v[6] - b[15]) < 0.01 and abs(v[7] - 1.5) < 0.05 and abs(v[10] - 1.5) < 0.001 and abs(v[11] - 1.5) < 0.001
    ok &= c
    if not c: msg.append((k, v, b))
# the corner handle scales like a room corner: wider / deeper with the mouse, the source moves with it; Ctrl = in proportion (height too)
# 0.378: the reflectors keep their place, length, angle and height (they used to scale with the area - the user wants them to stay)
def drag(mods):
    return "mouse 605 280 0 0\nframe\nmouse 605 280 1 %d\nframe\nmouse 650 300 1 %d\nframe\nmouse 700 320 1 %d\nframe\nmouse 700 320 0 0\nframe\nframe\n" % (mods, mods, mods)
v = run(enter + drag(0))
c2 = v[0] > 30 and v[1] > 33 and abs(v[12] - 20) < 0.01 and v[13] == 8; ok &= c2; msg.append(("corner drag", v))
v = run(enter + drag(2))
c3 = v[0] > 25 and v[13] > 9; ok &= c3; msg.append(("corner drag Ctrl", v))
# the Delay module helps the sound: alley (1) = a delay, meadow (5) = none
v = run(enter + click(245, 410) + click(200, int(98 + 1 * 17.8))); c4 = v[14] == 1; ok &= c4; msg.append(("alley delay", v))
v = run(enter + click(245, 410) + click(200, int(98 + 5 * 17.8))); c5 = v[14] == 0; ok &= c5; msg.append(("meadow no delay", v))
# Reflectors tab: click R1 = off / on again; power button = both off / on
tab4 = "var tb_vi 46\nvar tb_vv 4\nframe\nframe\n"
v = run(enter + tab4 + click(37, 436)); c6 = v[16] == 0 and v[17] == 1; ok &= c6; msg.append(("R1 off", v))
v = run(enter + tab4 + click(37, 436) + click(37, 436)); c7 = v[16] == 1; ok &= c7; msg.append(("R1 toggled back", v))
v = run(enter + tab4 + click(1066, 409)); c8 = v[15] == 1; ok &= c8; msg.append(("power off", v))
# Reset icon of the Free field tab (122, 409) after the Soccer field (index 4) -> Street again
v = run(enter + click(245, 410) + click(200, 169) + click(122, 409))
c1 = abs(v[0] - 20) < 0.05 and abs(v[1] - 30) < 0.05 and v[2] == 1 and v[3] == 1; ok &= c1; msg.append(("reset free field tab", v))
print("FFPRESETS PASS" if ok else "FFPRESETS FAIL %s" % msg)
