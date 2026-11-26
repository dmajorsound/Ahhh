# variables written both by the audio thread (@block/@sample) and the GUI (@gfx) - a shared name means a race
import re, sys
s = open(sys.argv[1]).read()
s = re.sub(r"//[^\n]*", "", s); s = re.sub(r"/\*.*?\*/", "", s, flags=re.S)
def sect(name):
    m = re.search(r"^@" + name + r"\b.*?$(.*?)(?=^@|\Z)", s, re.M | re.S); return m.group(1) if m else ""
def writes(t):
    t = re.sub(r'"[^"]*"', '""', t)
    return set(n.lower() for n in re.findall(r"(?<![\w.#\[])([A-Za-z_]\w*)\s*(?:[-+*/|&]?=)(?!=)", t))
init = sect("init")
# functions: name -> body writes (only non-local names)
funcs = {}
for m in re.finditer(r"function\s+(\w+)\s*\(([^)]*)\)\s*((?:local|instance)\s*\(([^)]*)\))?", s):
    name = m.group(1).lower(); params = set(p.strip().lower() for p in m.group(2).split(",") if p.strip())
    loc = set(p.strip().lower() for p in (m.group(4) or "").split(",") if p.strip())
    # body: until next "function " at line start or section
    rest = s[m.end():]; e = re.search(r"\n\s*function\s|\n@", rest); body = rest[:e.start()] if e else rest
    funcs[name] = (writes(body) - params - loc, body)
def closure(t):
    w = writes(t); seen = set(); todo = [f for f in funcs if re.search(r"\b" + f + r"\s*\(", t, re.I)]
    while todo:
        f = todo.pop()
        if f in seen: continue
        seen.add(f); w |= funcs[f][0]
        todo += [g for g in funcs if g not in seen and re.search(r"\b" + g + r"\s*\(", funcs[f][1], re.I)]
    return w
gfx_src = sect("gfx"); gfx_src = re.sub(r"function\s+\w+\s*\([^)]*\)(\s*(local|instance)\s*\([^)]*\))?", "", gfx_src)
audio = closure(sect("block") + sect("sample")); gui = closure(sect("gfx"))
both = sorted(n for n in audio & gui if not n.startswith("slider") and n not in ("i", "k", "j"))
print(len(both)); print(" ".join(both))
# narrow: written directly in the audio sections AND directly in the GUI section text (outside shared functions)
gfxbody = sect("gfx"); 
for m in list(re.finditer(r"function\s+\w+\s*\([^)]*\)", gfxbody))[::-1]:
    pass
ga = writes(sect("block") + sect("sample")); gg = writes(gfx_src)
d = sorted(n for n in ga & gg if not n.startswith("slider") and n not in ("i","k","j"))
print("DIRECT", len(d)); print(" ".join(d))
