# Tempo tools (Delay tab): Listen -> Stop listening -> close X must work and must not touch the module scale (0.339: tcd name collision)
import subprocess, sys, re
new = sys.argv[1]
env = dict(__import__("os").environ, SRC=new)
C = "var tb_basic 0;var tb_set 1;var tb_vi 46;var tb_vv 10;var tpon 1;frame;frame;mouse 952 145 0 0;frame;frame;mouse 952 145 1 0;frame;frame;mouse 952 145 0 0;frame;frame;audio 20 0.2;frame;mouse 952 145 1 0;frame;frame;mouse 952 145 0 0;frame;frame;print anaStp;audio 5 0.2;print anaOn;frame;frame;vmem vopt 35 1;mouse 1064 111 0 0;frame;frame;mouse 1064 111 1 0;frame;frame;mouse 1064 111 0 0;frame;frame;print tpon"
o = subprocess.run(["python3", "shot.py", "tpt", "1100", "700", C], capture_output=True, text=True, env=env).stdout
ok = "anaStp = 1" in o and "anaOn = 0" in o and "tpon = 0" in o and re.search(r"vopt\[35\.\.\]: 0\b", o)
print("TPTEST PASS" if ok else "TPTEST FAIL " + o.replace("\n", " "))
