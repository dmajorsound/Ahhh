# 0.372: the free-field reflectors (vopt[52..66]) are part of snapshots, A/B and undo: a saved state brings them back
import subprocess, sys, re
src = open(sys.argv[1]).read()
src = re.sub(r'slider_automate\((slider[0-9]+), [01]\)', r'slider_automate(\1)', src)
anchor = 'gfx_clear = -1;                          // never auto-clear'
assert anchor in src
probe = '''
tb_c == 1 ? ( vopt[53] = 5.5; vopt[60] = 7; saveslot(2); tb_c = 0; );
tb_c == 2 ? ( vopt[53] = 9; vopt[60] = 1; tb_c = 0; );
tb_c == 3 ? ( loadslot(2); tb_o1 = vopt[53]; tb_o2 = vopt[60]; tb_c = 0; );
tb_c == 4 ? ( vopt[53] = 3; abstore(0); vopt[53] = 8; abload(0); tb_o3 = vopt[53]; tb_c = 0; );
tb_c == 5 ? ( tbm = 4194304 + 150000; vopt[53] = 4; ucopy(tbm); vopt[53] = 9; tb_d1 = udiff(tbm); uapply(tbm); tb_o4 = vopt[53]; tb_d2 = udiff(tbm); tb_c = 0; );
'''
src = src.replace(anchor, probe + anchor, 1)
open('/tmp/rs_snap.jsfx', 'w').write(src)
open('/tmp/rs_snap.txt', 'w').write("var slider1 1\nframe\nframe\nvar tb_c 1\nframe\nvar tb_c 2\nframe\nvar tb_c 3\nframe\nprint tb_o1\nprint tb_o2\nvar tb_c 4\nframe\nprint tb_o3\nvar tb_c 5\nframe\nprint tb_d1\nprint tb_o4\nprint tb_d2\n")
r = subprocess.run(['./render0', '/tmp/rs_snap.jsfx', '320', '200', '/tmp/rs_snap.txt'], capture_output=True, text=True, cwd='/home/claude/host').stdout
v = dict((k, float(x)) for k, x in re.findall(r'(tb_\w+) = ([-0-9.e+]+)', r))
ok = v.get('tb_o1') == 5.5 and v.get('tb_o2') == 7 and v.get('tb_o3') == 3 and v.get('tb_d1') == 1 and v.get('tb_o4') == 4 and v.get('tb_d2') == 0
print("REFLSNAP PASS" if ok else "REFLSNAP FAIL", "snapshot %s/%s A-B %s undo diff %s -> value %s diff after %s" % (v.get('tb_o1'), v.get('tb_o2'), v.get('tb_o3'), v.get('tb_d1'), v.get('tb_o4'), v.get('tb_d2')))
