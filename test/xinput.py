# minimal XTest driver: python3 xinput.py move x y | click x y [button] | drag x1 y1 x2 y2 | key keysym
import ctypes, sys, time
x11 = ctypes.CDLL('libX11.so.6'); xt = ctypes.CDLL('libXtst.so.6')
x11.XOpenDisplay.restype = ctypes.c_void_p
x11.XStringToKeysym.restype = ctypes.c_ulong
d = ctypes.c_void_p(x11.XOpenDisplay(None))
def flush(): x11.XFlush(d); time.sleep(0.08)
def move(x, y): xt.XTestFakeMotionEvent(d, 0, int(x), int(y), 0); flush()
def btn(b, down): xt.XTestFakeButtonEvent(d, b, down, 0); flush()
a = sys.argv[1:]
if a[0] == 'move': move(a[1], a[2])
elif a[0] == 'click':
    move(a[1], a[2]); b = int(a[3]) if len(a) > 3 else 1; btn(b, 1); btn(b, 0)
elif a[0] == 'drag':
    move(a[1], a[2]); btn(1, 1)
    x1, y1, x2, y2 = map(float, a[1:5])
    for i in range(1, 11): move(x1 + (x2 - x1) * i / 10, y1 + (y2 - y1) * i / 10)
    btn(1, 0)
elif a[0] == 'slowdrag':
    x1, y1, x2, y2 = map(float, a[1:5])
    move(x1, y1); time.sleep(0.3); btn(1, 1); time.sleep(0.3)
    for i in range(1, 31): move(x1 + (x2 - x1) * i / 30, y1 + (y2 - y1) * i / 30)
    time.sleep(0.3); btn(1, 0)
elif a[0] == 'key':
    kc = x11.XKeysymToKeycode(d, x11.XStringToKeysym(a[1].encode()))
    xt.XTestFakeKeyEvent(d, kc, 1, 0); flush(); xt.XTestFakeKeyEvent(d, kc, 0, 0); flush()
elif a[0] == 'wheel':
    move(a[1], a[2]); b = 4 if int(a[3]) > 0 else 5
    for _ in range(abs(int(a[3]))): btn(b, 1); btn(b, 0)
