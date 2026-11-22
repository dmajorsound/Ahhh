// native: run the generated C++ engine. usage: natrender params.txt in.f64 out.f64 [srate] [block]
#include "engine.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
static std::vector<double> readf(const char* p) { std::ifstream f(p, std::ios::binary); std::vector<char> b((std::istreambuf_iterator<char>(f)), {}); std::vector<double> d(b.size() / 8); memcpy(d.data(), b.data(), d.size() * 8); return d; }
int main(int argc, char** argv) {
    if (argc < 4) return 2;
    double sr = argc > 4 ? atof(argv[4]) : 48000; int bs = argc > 5 ? atoi(argv[5]) : 256;
    rs::Engine e; e.setSampleRate(sr); e.setBlockSize(bs);
    FILE* pf = fopen(argv[1], "r"); int n; double v;
    while (pf && fscanf(pf, "%d %lf", &n, &v) == 2) e.setSlider(n, v);
    if (pf) fclose(pf);
    std::vector<double> in = readf(argv[2]); size_t frames = in.size() / 2;
    std::vector<double> out(in.size()), iL(bs), iR(bs), oL(bs), oR(bs);
    rs::TimeInfo ti;
    for (size_t pos = 0; pos < frames; pos += bs) {
        int nf = (int)std::min<size_t>(bs, frames - pos);
        for (int i = 0; i < nf; i++) { iL[i] = in[2 * (pos + i)]; iR[i] = in[2 * (pos + i) + 1]; }
        ti.position = pos / sr; ti.beat = ti.position * 2;
        const double* ins[2] = {iL.data(), iR.data()}; double* outs[2] = {oL.data(), oR.data()};
        e.process(ins, outs, 2, 2, nf, ti);
        for (int i = 0; i < nf; i++) { out[2 * (pos + i)] = oL[i]; out[2 * (pos + i) + 1] = oR[i]; }
    }
    std::ofstream o(argv[3], std::ios::binary); o.write((const char*)out.data(), out.size() * 8);
    return 0;
}
