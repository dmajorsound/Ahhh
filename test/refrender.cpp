// reference: run the original JSFX through ysfx. usage: refrender fx.jsfx params.txt in.f64 out.f64 [srate] [block]; NCH=6 for six interleaved channels
#include "ysfx.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
static int nch() { const char* e = getenv("NCH"); int n = e ? atoi(e) : 2; return n < 1 ? 1 : (n > 6 ? 6 : n); }
#include <iterator>
static std::vector<double> readf(const char* p) { std::ifstream f(p, std::ios::binary); std::vector<char> b((std::istreambuf_iterator<char>(f)), {}); std::vector<double> d(b.size() / 8); memcpy(d.data(), b.data(), d.size() * 8); return d; }
int main(int argc, char** argv) {
    if (argc < 5) return 2;
    double sr = argc > 5 ? atof(argv[5]) : 48000; int bs = argc > 6 ? atoi(argv[6]) : 256;
    ysfx_config_t* cfg = ysfx_config_new();
    ysfx_t* fx = ysfx_new(cfg);
    if (!ysfx_load_file(fx, argv[1], 0)) { fprintf(stderr, "load failed\n"); return 1; }
    if (!ysfx_compile(fx, 0)) { fprintf(stderr, "compile failed\n"); return 1; }
    ysfx_set_sample_rate(fx, sr); ysfx_set_block_size(fx, bs);
    FILE* pf = fopen(argv[2], "r"); int n; double v;
    while (pf && fscanf(pf, "%d %lf", &n, &v) == 2) ysfx_slider_set_value(fx, n - 1, v);
    if (pf) fclose(pf);
    const int N = nch(); std::vector<double> in = readf(argv[3]); size_t frames = in.size() / N;
    std::vector<double> out(in.size());
    std::vector<std::vector<double>> ib(N, std::vector<double>(bs)), ob(N, std::vector<double>(bs)); const double* ins[6]; double* outs[6]; for (int c = 0; c < N; c++) { ins[c] = ib[c].data(); outs[c] = ob[c].data(); }
    ysfx_time_info_t ti{}; ti.tempo = 120; ti.playback_state = ysfx_playback_playing; ti.time_signature[0] = 4; ti.time_signature[1] = 4;
    for (size_t pos = 0; pos < frames; pos += bs) {
        uint32_t nf = (uint32_t)std::min<size_t>(bs, frames - pos);
        for (uint32_t i = 0; i < nf; i++) for (int c = 0; c < N; c++) ib[c][i] = in[N * (pos + i) + c];
        ti.time_position = pos / sr; ti.beat_position = ti.time_position * 2;
        ysfx_set_time_info(fx, &ti);
        ysfx_process_double(fx, ins, outs, N, N, nf);
        for (uint32_t i = 0; i < nf; i++) for (int c = 0; c < N; c++) out[N * (pos + i) + c] = ob[c][i];
    }
    std::ofstream o(argv[4], std::ios::binary); o.write((const char*)out.data(), out.size() * 8);
    ysfx_free(fx); ysfx_config_free(cfg);
    return 0;
}
