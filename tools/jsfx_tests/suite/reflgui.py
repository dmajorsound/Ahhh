# 0.362 REFLECTORS GUI: the handle in the plan moves the reflector, a knob changes it, the material chips switch it, Reset clears it
import subprocess, sys, re
s = open(sys.argv[1]).read()
s = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', s)
anchor = 'gfx_clear = -1;                          // never auto-clear'
assert anchor in s
s = s.replace(anchor, 'tb_rf > 0 ? ( vopt[52] = 1; vopt[53] = 5; vopt[54] = 2.2; vopt[55] = 90; vopt[56] = 5; vopt[57] = 5; vopt[40] = 0; vopt[46] = 4; vopt[11] = 0; tb_rf = 0; );\ntb_a0 = vopt[52]; tb_a1 = vopt[53]; tb_a2 = vopt[54]; tb_a3 = vopt[55]; tb_a4 = vopt[58]; tb_a5 = rflSel;\n' + anchor, 1)
open('/tmp/rg_t.jsfx', 'w').write(s)
def run(cmd, n):
    open('/tmp/rg.txt', 'w').write("slider 0 1\nvar tb_rf 1\nframe\nframe\nframe\n" + cmd + "".join("print tb_a%d\n" % i for i in range(6)))
    r = subprocess.run(['./render0', '/tmp/rg_t.jsfx', '1100', '700', '/tmp/rg.txt'], capture_output=True, text=True).stdout
    return [float(x) for k, x in re.findall(r"(tb_a\d) = ([-0-9.e]+)", r)]
ok = True; msg = []
# handle drag in the plan: from (631,197) to (560,150) -> X smaller, Y smaller
v = run("mouse 631 197 0 0\nframe\nmouse 631 197 1 0\nframe\nmouse 600 170 1 0\nframe\nmouse 560 150 1 0\nframe\nmouse 560 150 0 0\nframe\nframe\n", 0)
c1 = len(v) == 6 and v[1] < 4.3 and v[2] < 2.0; ok &= c1; msg.append(("drag", v))
# material chip Glass (x ~ 509, y 436)
v = run("mouse 509 436 0 0\nframe\nmouse 509 436 1 0\nframe\nmouse 509 436 0 0\nframe\nframe\n", 0)
c2 = len(v) == 6 and v[0] == 2; ok &= c2; msg.append(("glass", v))
# R2 chip (x 75, y 436) then Facade chip: R2 gets defaults
v = run("mouse 75 436 0 0\nframe\nmouse 75 436 1 0\nframe\nmouse 75 436 0 0\nframe\nframe\nmouse 345 436 0 0\nframe\nmouse 345 436 1 0\nframe\nmouse 345 436 0 0\nframe\nframe\n", 0)
c3 = len(v) == 6 and v[4] > 0.5; ok &= c3; msg.append(("r2 default", v))
# Angle knob drag up (0.379: the knobs sit under the material row, as in the Free field tab - y 490 instead of 553)
v = run("mouse 460 490 0 0\nframe\nmouse 460 490 1 0\nframe\nmouse 460 460 1 0\nframe\nmouse 460 440 1 0\nframe\nmouse 460 440 0 0\nframe\nframe\n", 0)
c4 = len(v) == 6 and v[3] > 95; ok &= c4; msg.append(("angle", v))
print("REFLGUI PASS" if ok else "REFLGUI FAIL %s" % msg)
