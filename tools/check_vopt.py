#!/usr/bin/env python3
# Checks the split "view options / sound settings" of the script's vopt block that src/engine.cpp relies on when a
# preset is loaded into a running instance (the view stays, the sound comes from the preset).
#   python3 tools/check_vopt.py jsfx/Ahh.jsfx        exit code 1 = engine.cpp (isViewOption) needs an update
import sys, os, re
sys.setrecursionlimit(200000)
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import parseall

SOUND = {18, 49, 68, 69} | set(range(52, 67))     # must match isViewOption() in src/engine.cpp
AUDIO_READS_VIEW = {11}                           # Basic mode switches solo off; it is still the view and is kept

def main(path):
    secs, funcs, trees = parseall.load(path)
    def scan(n, idx, calls, dyn):
        if n is None or not hasattr(n, 't'): return
        if n.t == 'mem':
            a = n.a[0]
            if a.t == 'var' and a.a[0] == 'vopt': idx.add(0)
            elif a.t == '+' and a.a[0].t == 'var' and a.a[0].a[0] == 'vopt':
                if a.a[1].t == 'num': idx.add(int(a.a[1].a[0]))
                else: dyn.append(n.line)
        if n.t == 'call' and n.a[0] in funcs: calls.add(n.a[0])
        for x in n.a:
            if hasattr(x, 't'): scan(x, idx, calls, dyn)
    info = {}
    for name, f in funcs.items():
        i, c, d = set(), set(), []; scan(f.body, i, c, d); info[name] = (i, c, d)
    audio, dyn = set(), []
    for sec in ('block', 'sample'):
        i, c, d = set(), set(), []; scan(trees.get(sec), i, c, d); audio |= i; dyn += d
        seen, st = set(), list(c)
        while st:
            f = st.pop()
            if f in seen: continue
            seen.add(f); st.extend(info[f][1]); audio |= info[f][0]; dyn += info[f][2]
    src = open(path, encoding='utf-8').read()
    lines = src.split('\n')
    errors = []
    extra = sorted(audio - SOUND - AUDIO_READS_VIEW - {0})
    if extra: errors.append('the audio code reads vopt%s: not listed as sound settings' % extra)
    # computed indices in the audio code: only the reflector block RFB + n
    for l in sorted(set(dyn)):
        if 'RFB' not in lines[l - 1] and 'rfO' not in lines[l - 1]:
            errors.append('line %d: computed vopt index outside the reflector block: %s' % (l, lines[l - 1].strip()[:100]))
    if not re.search(r'\bRFB = 52;', src): errors.append('RFB is no longer 52 (reflectors: vopt[52 .. 66])')
    if not re.search(r'\bvopt = 2048;', src): errors.append('vopt is no longer at 2048')
    if not re.search(r'ser_so = 70;', src): errors.append('@serialize no longer writes 70 view options')
    for e in errors: print('check_vopt: ' + e)
    print('check_vopt: %s (audio reads vopt%s, reflector block by index on %d lines)' % ('FAILED' if errors else 'ok', sorted(audio), len(set(dyn))))
    return 1 if errors else 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1]))
