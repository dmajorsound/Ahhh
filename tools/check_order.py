#!/usr/bin/env python3
"""A JSFX function must be defined above its first call - REAPER refuses the effect otherwise
("undefined function"). The C++ translation does not care about the order, so this is checked here.

    python3 tools/check_order.py jsfx/Ahh.jsfx
"""
import re, sys

def main(path):
    src = open(path, encoding='utf-8').read()
    src = re.sub(r'"(?:[^"\\\n]|\\.)*"', '""', src)          # strings
    src = re.sub(r"'(?:[^'\\\n]|\\.)*'", "''", src)          # character constants
    src = re.sub(r'/\*.*?\*/', lambda m: '\n' * m.group(0).count('\n'), src, flags=re.S)
    src = re.sub(r'//[^\n]*', '', src)
    body = re.search(r'^@init\b', src, flags=re.M)             # the header (slider lines) holds no code
    start = body.start() if body else 0
    defs = {}
    for m in re.finditer(r'\bfunction\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(', src):
        defs.setdefault(m.group(1), m.start())
    bad = []
    for m in re.finditer(r'(?<![A-Za-z0-9_.])([A-Za-z_][A-Za-z0-9_]*)\s*\(', src):
        name = m.group(1)
        if name in defs and start <= m.start() < defs[name]:
            bad.append((src.count('\n', 0, m.start()) + 1, name, src.count('\n', 0, defs[name]) + 1))
    for line, name, dline in bad: print('line %d: %s() is called above its definition (line %d)' % (line, name, dline))
    if not bad: print('check_order: ok (%d functions)' % len(defs))
    return 1 if bad else 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1] if len(sys.argv) > 1 else 'jsfx/Ahh.jsfx'))
