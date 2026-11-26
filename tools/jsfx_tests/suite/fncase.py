import re, sys, collections
d = collections.defaultdict(set)
for l in open(sys.argv[1]):
    m = re.match(r"\s*function\s+([A-Za-z_][A-Za-z0-9_.]*)", l.split("//")[0])
    if m: d[m.group(1).lower()].add(m.group(1))
bad = [n for n, v in d.items() if len(v) > 1]
print("FNBAD", " ".join(sorted("/".join(sorted(d[n])) for n in bad)) if bad else "none")
