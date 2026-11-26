import re, sys
bad = []
for n, l in enumerate(open(sys.argv[1]), 1):
    code = l.split("//")[0]
    for m in re.finditer(r"4194304\s*\+\s*(\d+)", code):
        if int(m.group(1)) >= 121000 and "ALC =" not in code: bad.append("%d: %s" % (n, code.strip()[:80]))
print("MEMBAD", "; ".join(bad) if bad else "none")
