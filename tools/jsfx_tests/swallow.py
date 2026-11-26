import re,sys
src=open(sys.argv[1]).read().split('\n')
code=[];com=[]
for i,l in enumerate(src):
    # split at first // not inside string
    q=False;cut=None
    for j,ch in enumerate(l):
        if ch=='"': q=not q
        if not q and l[j:j+2]=='//': cut=j;break
    code.append(l if cut is None else l[:cut]); com.append('' if cut is None else l[cut:])
ctext='\n'.join(code).lower()
assigned=set(m.group(1) for m in re.finditer(r'\b([a-z_][a-z0-9_.]*)\s*(?:\+|-|\*|/)?=(?!=)',ctext))
used=set(re.findall(r'\b([a-z_][a-z0-9_.]*)\b',ctext))
for i,c in enumerate(com):
    for m in re.finditer(r'(?:;|^//)\s*([A-Za-z_][A-Za-z0-9_.]*)\s*=\s*[^=;]+;',c):
        n=m.group(1).lower()
        if n not in assigned and n in used:
            print(i+1,n,c[:160])
# 0.325: code-like statements after a // (an assignment that reads a slider or calls a function, ended by ;)
for i,c in enumerate(com):
    if re.search(r'(?:^//|[\s;(])[A-Za-z_][A-Za-z0-9_.]*\s*=\s*[^=;"]*(?:slider\d+|floor\(|min\(|max\(|sqrt\()[^;"]*;', c):
        print(i+1,'CODE?',c[:160])

# 0.384: a compound assignment (+=, -=, *=) of a known variable after a // - e.g. "ukey += ..." lost behind a comment
for i,c in enumerate(com):
    for m in re.finditer(r'(?:\)|;|^//[^;]*?)\s*([A-Za-z_][A-Za-z0-9_.]*)\s*(?:\+|-|\*)=\s*[^=;]+;', c):
        n=m.group(1).lower()
        if n in assigned and n in used: print(i+1,'COMPOUND?',n,c[:160])
