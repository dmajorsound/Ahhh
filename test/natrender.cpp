// native: run the generated C++ engine. usage: natrender params.txt in.f64 out.f64 [srate] [block]; NCH=6 for six interleaved channels
#include "engine.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
static int nch() { const char* e = getenv("NCH"); int n = e ? atoi(e) : 2; return n < 1 ? 1 : (n > 6 ? 6 : n); }
static std::vector<double> readf(const char* p) { std::ifstream f(p, std::ios::binary); std::vector<char> b((std::istreambuf_iterator<char>(f)), {}); std::vector<double> d(b.size() / 8); memcpy(d.data(), b.data(), d.size() * 8); return d; }
int main(int argc, char** argv) {
    if (argc < 4) return 2;
    double sr = argc > 4 ? atof(argv[4]) : 48000; int bs = argc > 5 ? atoi(argv[5]) : 256;
    rs::Engine e; e.setSampleRate(sr); e.setBlockSize(bs);
    FILE* pf = fopen(argv[1], "r"); int n; double v;
    while (pf && fscanf(pf, "%d %lf", &n, &v) == 2) e.setSlider(n, v);
    if (pf) fclose(pf);
    const int N = nch(); std::vector<double> in = readf(argv[2]); size_t frames = in.size() / N;
    std::vector<double> out(in.size()); std::vector<std::vector<double>> ib(N, std::vector<double>(bs)), ob(N, std::vector<double>(bs)); const double* ins[6]; double* outs[6]; for (int c = 0; c < N; c++) { ins[c] = ib[c].data(); outs[c] = ob[c].data(); }
    rs::TimeInfo ti;
    for (size_t pos = 0; pos < frames; pos += bs) {
        int nf = (int)std::min<size_t>(bs, frames - pos);
        for (int i = 0; i < nf; i++) for (int c = 0; c < N; c++) ib[c][i] = in[N * (pos + i) + c];
        ti.position = pos / sr; ti.beat = ti.position * 2;
        e.process(ins, outs, N, N, nf, ti);
        for (int i = 0; i < nf; i++) for (int c = 0; c < N; c++) out[N * (pos + i) + c] = ob[c][i];
    }
    std::ofstream o(argv[3], std::ios::binary); o.write((const char*)out.data(), out.size() * 8);
    return 0;
}
