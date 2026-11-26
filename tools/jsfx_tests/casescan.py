import re,collections,sys
s=open(sys.argv[1]).read()
# strip comments and strings
s=re.sub(r'//[^\n]*','',s); s=re.sub(r'"[^"\n]*"','""',s)
ids=re.findall(r'\b[A-Za-z_][A-Za-z0-9_]*\b',s)
groups=collections.defaultdict(set)
for i in ids: groups[i.lower()].add(i)
# locals: names declared in local(...) are shadowed inside the function only - still report, but mark
locs=set()
for m in re.finditer(r'local\(([^)]*)\)',s):
    for n in m.group(1).split(','): locs.add(n.strip().lower())
fnames=set(m.group(1).lower() for m in re.finditer(r'function\s+([A-Za-z_][A-Za-z0-9_]*)',s))
words={'as','back','bpm','clockwise','door','eq','ex','ey','face','facing','floor','front','high','hz','input','left','listener','low','mode','model','off','on','output','pass','pre','reverb','right','room','size','snapshot','source','tempo','top','tv','wall','window','d','h','k','l','q','r','v','w','x','y'}
for k,v in sorted(groups.items()):
    if len(v)>1 and k not in words and k not in fnames:
        print(k, sorted(v), "(local)" if k in locs else "")
