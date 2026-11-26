// multichannel test host: render6 file.jsfx NCH in.raw out.raw [slider_index0=value ...]   (raw = interleaved float32, 48 kHz, blocks of 256)
#include "ysfx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
static void logr(intptr_t, ysfx_log_level l, const char *m) { fprintf(stderr, "[%s] %s\n", ysfx_log_level_string(l), m); }
int main(int argc, char **argv) {
    if (argc < 5) { fprintf(stderr, "usage: render6 file.jsfx NCH in.raw out.raw [i=v ...]\n"); return 1; }
    int nch = atoi(argv[2]); const int BS = 256;
    ysfx_config_t *cfg = ysfx_config_new(); ysfx_set_log_reporter(cfg, &logr);
    ysfx_t *fx = ysfx_new(cfg);
    if (!ysfx_load_file(fx, argv[1], 0)) return 2;
    if (!ysfx_compile(fx, 0)) return 3;
    ysfx_set_sample_rate(fx, 48000); ysfx_set_block_size(fx, BS); ysfx_init(fx);
    for (int i = 5; i < argc; i++) { int k; double v; if (sscanf(argv[i], "%d=%lf", &k, &v) == 2) ysfx_slider_set_value(fx, k, v); }
    FILE *fi = fopen(argv[3], "rb"); FILE *fo = fopen(argv[4], "wb"); if (!fi || !fo) return 4;
    std::vector<float> inter(BS * nch), o(BS * nch);
    std::vector<std::vector<float>> in(nch, std::vector<float>(BS)), out(nch, std::vector<float>(BS));
    std::vector<const float *> pi(nch); std::vector<float *> po(nch);
    for (int c = 0; c < nch; c++) { pi[c] = in[c].data(); po[c] = out[c].data(); }
    while (fread(inter.data(), sizeof(float), BS * nch, fi) == (size_t)(BS * nch)) {
        for (int i = 0; i < BS; i++) for (int c = 0; c < nch; c++) in[c][i] = inter[i * nch + c];
        ysfx_process_float(fx, pi.data(), po.data(), nch, nch, BS);
        for (int i = 0; i < BS; i++) for (int c = 0; c < nch; c++) o[i * nch + c] = out[c][i];
        fwrite(o.data(), sizeof(float), BS * nch, fo);
    }
    fclose(fo); fclose(fi); return 0;
}
