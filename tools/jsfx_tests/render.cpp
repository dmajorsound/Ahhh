// minimal JSFX host: compile, run audio blocks, run @gfx with scripted mouse input, save PPM frames
#include "ysfx.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <unistd.h>
static void logr(intptr_t, ysfx_log_level l, const char *m) { fprintf(stderr, "[%s] %s\n", ysfx_log_level_string(l), m); }
int main(int argc, char **argv) {
    if (argc < 5) { fprintf(stderr, "usage: render file.jsfx W H script\n"); return 1; }
    const char *path = argv[1]; int W = atoi(argv[2]), H = atoi(argv[3]); const char *script = argv[4];
    ysfx_config_t *cfg = ysfx_config_new(); ysfx_set_log_reporter(cfg, &logr);
    ysfx_t *fx = ysfx_new(cfg);
    if (!ysfx_load_file(fx, path, 0)) { fprintf(stderr, "load failed\n"); return 2; }
    if (!ysfx_compile(fx, 0)) { fprintf(stderr, "compile failed\n"); return 3; }
    ysfx_set_sample_rate(fx, 48000); ysfx_set_block_size(fx, 256); ysfx_init(fx);
    printf("pdc %g\n", ysfx_get_pdc_delay(fx));
    std::vector<uint8_t> px(W * H * 4);
    ysfx_gfx_config_t gc = {}; gc.pixel_width = W; gc.pixel_height = H; gc.pixels = px.data(); gc.scale_factor = 1.0;
    ysfx_gfx_setup(fx, &gc);
    std::vector<float> a(256), b(256), oa(256), ob(256);
    auto audio = [&](int blocks, float amp) {
        for (int k = 0; k < blocks; k++) {
            for (int i = 0; i < 256; i++) { a[i] = b[i] = amp * (float)(((rand() % 2000) - 1000) / 1000.0); }
            const float *ins[2] = {a.data(), b.data()}; float *outs[2] = {oa.data(), ob.data()};
            ysfx_process_float(fx, ins, outs, 2, 2, 256);
        }
    };
    static int gbs = 256; static double gmaxms = 0; ysfx_state_t *st = nullptr; FILE *sf = fopen(script, "r"); char line[512]; int mx = 0, my = 0, btn = 0, mods = 0;
    while (fgets(line, sizeof line, sf)) {
        char cmd[32]; if (sscanf(line, "%31s", cmd) != 1 || cmd[0] == '#') continue;
        if (!strcmp(cmd, "audio")) { int n; float amp; sscanf(line, "%*s %d %f", &n, &amp); audio(n, amp); }
        else if (!strcmp(cmd, "sine")) { int nb; float f, amp; char fn[256]; sscanf(line, "%*s %d %f %f %255s", &nb, &f, &amp, fn); FILE *o = fopen(fn, "ab");
            static double ph = 0; int sb = gbs > 0 ? gbs : 256; if ((int)a.size() < sb) { a.resize(sb); b.resize(sb); oa.resize(sb); ob.resize(sb); }
            for (int k = 0; k < nb * 256 / sb; k++) { for (int i = 0; i < sb; i++) { a[i] = b[i] = amp * (float)sin(ph); ph += 2 * M_PI * f / 48000; }
            const float *ins[2] = {a.data(), b.data()}; float *outs[2] = {oa.data(), ob.data()}; ysfx_process_float(fx, ins, outs, 2, 2, sb);
            for (int i = 0; i < sb; i++) { fwrite(&oa[i], 4, 1, o); fwrite(&ob[i], 4, 1, o); } } fclose(o); }
        else if (!strcmp(cmd, "sleep")) { int ms; sscanf(line, "%*s %d", &ms); usleep(ms * 1000); }
        else if (!strcmp(cmd, "maxms")) { printf("maxms %.3f (budget %.3f)\n", gmaxms, gbs * 1000.0 / ysfx_get_sample_rate(fx)); gmaxms = 0; }
        else if (!strcmp(cmd, "bsize")) { sscanf(line, "%*s %d", &gbs); ysfx_set_block_size(fx, gbs); }
        else if (!strcmp(cmd, "noise")) { int nb; float amp; char fn[256]; sscanf(line, "%*s %d %f %255s", &nb, &amp, fn); FILE *o = fopen(fn, "ab");
            std::vector<float> A(gbs), B(gbs), OA(gbs), OB(gbs);
            static double lp = 0; for (int k = 0; k < nb; k++) { for (int i = 0; i < gbs; i++) { double w = ((rand() % 20001) - 10000) / 10000.0; lp = 0.97 * lp + 0.03 * w; A[i] = B[i] = amp * (float)(w * 0.3 + lp * 3); }
            const float *ins[2] = {A.data(), B.data()}; float *outs[2] = {OA.data(), OB.data()};
              auto t0 = std::chrono::steady_clock::now(); ysfx_process_float(fx, ins, outs, 2, 2, gbs);
              double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); if (ms > gmaxms) gmaxms = ms;
            for (int i = 0; i < gbs; i++) { fwrite(&OA[i], 4, 1, o); fwrite(&OB[i], 4, 1, o); } } fclose(o); }
        else if (!strcmp(cmd, "clicks")) { int nb, per; float amp; char fn[256]; sscanf(line, "%*s %d %d %f %255s", &nb, &per, &amp, fn); FILE *o = fopen(fn, "ab");
            static long cnt = 0; for (int k = 0; k < nb; k++) { for (int i = 0; i < 256; i++) { a[i] = b[i] = (cnt % per == 0) ? amp : 0.f; cnt++; }
            const float *ins[2] = {a.data(), b.data()}; float *outs[2] = {oa.data(), ob.data()}; ysfx_process_float(fx, ins, outs, 2, 2, 256);
            for (int i = 0; i < 256; i++) { fwrite(&oa[i], 4, 1, o); fwrite(&ob[i], 4, 1, o); } } fclose(o); }
        else if (!strcmp(cmd, "blkmax")) { int nb, bs; sscanf(line, "%*s %d %d", &nb, &bs); double mxm = 0, sum = 0;
            std::vector<float> A(bs), B(bs), OA(bs), OB(bs); ysfx_set_block_size(fx, bs);
            for (int k = 0; k < nb; k++) { ysfx_slider_set_value(fx, 9, 3 + 2 * sin(k / 40.0)); ysfx_slider_set_value(fx, 10, 2.5 + 1.5 * cos(k / 55.0));
              for (int i = 0; i < bs; i++) A[i] = B[i] = 0.3f * sin(i * 0.05);
              const float *ins[2] = {A.data(), B.data()}; float *outs[2] = {OA.data(), OB.data()};
              auto t0 = std::chrono::steady_clock::now(); ysfx_process_float(fx, ins, outs, 2, 2, bs);
              double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); sum += ms; if (ms > mxm) mxm = ms; }
            printf("moving source, block %d: avg %.3f ms, max %.3f ms (budget %.3f ms)\n", bs, sum / nb, mxm, bs / 48.0); }
        else if (!strcmp(cmd, "play")) { int st; double pos = 0; sscanf(line, "%*s %d %lf", &st, &pos); ysfx_time_info_t ti{}; ti.tempo = 120; ti.time_position = pos; ti.playback_state = st; ti.time_signature[0] = 4; ti.time_signature[1] = 4; ysfx_set_time_info(fx, &ti); }
        else if (!strcmp(cmd, "rawin")) { int nb; char fi[256], fo[256]; sscanf(line, "%*s %d %255s %255s", &nb, fi, fo); FILE *in = fopen(fi, "rb"); FILE *o = fopen(fo, "ab");
            int sb2 = gbs > 0 ? gbs : 256; if ((int)a.size() < sb2) { a.resize(sb2); b.resize(sb2); oa.resize(sb2); ob.resize(sb2); } for (int k = 0; k < nb; k++) { for (int i = 0; i < sb2; i++) { float v[2] = {0, 0}; if (in && fread(v, 4, 2, in) != 2) { v[0] = v[1] = 0; } a[i] = v[0]; b[i] = v[1]; }
            const float *ins[2] = {a.data(), b.data()}; float *outs[2] = {oa.data(), ob.data()}; ysfx_process_float(fx, ins, outs, 2, 2, sb2);
            for (int i = 0; i < sb2; i++) { fwrite(&oa[i], 4, 1, o); fwrite(&ob[i], 4, 1, o); } } if (in) fclose(in); fclose(o); }
        else if (!strcmp(cmd, "noiseL")) { int nb; float amp; char fn[256]; sscanf(line, "%*s %d %f %255s", &nb, &amp, fn); FILE *o = fopen(fn, "ab");
            for (int k = 0; k < nb; k++) { for (int i = 0; i < 256; i++) { a[i] = amp * (float)(((rand() % 2000) - 1000) / 1000.0); b[i] = 0.25f * a[i]; }
            const float *ins[2] = {a.data(), b.data()}; float *outs[2] = {oa.data(), ob.data()}; ysfx_process_float(fx, ins, outs, 2, 2, 256);
            for (int i = 0; i < 256; i++) { fwrite(&oa[i], 4, 1, o); fwrite(&ob[i], 4, 1, o); } } fclose(o); }
        else if (!strcmp(cmd, "mouse")) { sscanf(line, "%*s %d %d %d %d", &mx, &my, &btn, &mods); ysfx_gfx_update_mouse(fx, mods, mx, my, btn, 0, 0); }
        else if (!strcmp(cmd, "srate")) { double r; sscanf(line, "%*s %lf", &r); ysfx_set_sample_rate(fx, r); ysfx_init(fx); }
        else if (!strcmp(cmd, "key")) { unsigned k; sscanf(line, "%*s %u", &k); ysfx_gfx_add_key(fx, 0, k, true); }
        else if (!strcmp(cmd, "keys")) { char t[256] = {0}; sscanf(line, "%*s %255[^\n]", t); for (char *c = t; *c; c++) ysfx_gfx_add_key(fx, 0, (unsigned char)*c, true); }
        else if (!strcmp(cmd, "wheel")) { float w; sscanf(line, "%*s %f", &w); ysfx_gfx_update_mouse(fx, mods, mx, my, btn, w, 0); }
        else if (!strcmp(cmd, "timeframes")) { int n; sscanf(line, "%*s %d", &n); double mx_ = 0, sum = 0;
            for (int i = 0; i < n; i++) { audio(4, 0.3f); auto t0 = std::chrono::steady_clock::now(); ysfx_gfx_run(fx); double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); sum += ms; if (ms > mx_) mx_ = ms; }
            printf("gfx frames: avg %.2f ms, max %.2f ms\n", sum / n, mx_); }
        else if (!strcmp(cmd, "timeaudio")) { int n; sscanf(line, "%*s %d", &n); auto t0 = std::chrono::steady_clock::now(); audio(n, 0.3f); double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count(); printf("audio: %.3f ms per 256-sample block (budget 5.33 ms)\n", ms / n); }
        else if (!strcmp(cmd, "frame")) { int n = 1; sscanf(line, "%*s %d", &n); for (int i = 0; i < n; i++) ysfx_gfx_run(fx); }
        else if (!strcmp(cmd, "var")) { char nm[64]; double v; sscanf(line, "%*s %63s %lf", nm, &v); ysfx_real *p = ysfx_find_var(fx, nm); if (p) *p = v; else fprintf(stderr, "no var %s\n", nm); }
        else if (!strcmp(cmd, "print")) { char nm[64]; sscanf(line, "%*s %63s", nm); ysfx_real *p = ysfx_find_var(fx, nm); printf("%s = %g\n", nm, p ? *p : NAN); }
        else if (!strcmp(cmd, "slider")) { int i; double v; sscanf(line, "%*s %d %lf", &i, &v); ysfx_slider_set_value(fx, i, v); }
        else if (!strcmp(cmd, "getslider")) { int i; sscanf(line, "%*s %d", &i); printf("slider%d = %g\n", i, ysfx_slider_get_value(fx, i)); }
        else if (!strcmp(cmd, "savestate")) { if (st) ysfx_state_free(st); st = ysfx_save_state(fx); printf("state %zu bytes\n", st ? st->data_size : 0); }
        else if (!strcmp(cmd, "writestate")) { char fn[256]; sscanf(line, "%*s %255s", fn); ysfx_state_t *q = ysfx_save_state(fx); FILE *o = fopen(fn, "wb"); fwrite(q->data, 1, q->data_size, o); fclose(o);
            FILE *o2 = fopen((std::string(fn) + ".sl").c_str(), "wb"); fwrite(q->sliders, sizeof(ysfx_state_slider_t), q->slider_count, o2); fclose(o2); printf("wrote %zu\n", q->data_size); ysfx_state_free(q); }
        else if (!strcmp(cmd, "readstate")) { char fn[256]; sscanf(line, "%*s %255s", fn); FILE *i = fopen(fn, "rb"); std::vector<uint8_t> d(1 << 20); size_t n = fread(d.data(), 1, d.size(), i); fclose(i);
            FILE *i2 = fopen((std::string(fn) + ".sl").c_str(), "rb"); std::vector<ysfx_state_slider_t> sl(256); size_t ns = fread(sl.data(), sizeof(ysfx_state_slider_t), 256, i2); fclose(i2);
            ysfx_state_t q{}; q.sliders = sl.data(); q.slider_count = ns; q.data = d.data(); q.data_size = n; printf("read %zu load %d\n", n, (int)ysfx_load_state(fx, &q)); }
        else if (!strcmp(cmd, "loadstate")) { if (st) printf("load %d\n", (int)ysfx_load_state(fx, st)); }
        else if (!strcmp(cmd, "vmem")) { unsigned a, n; char nm[64]; sscanf(line, "%*s %63s %u %u", nm, &a, &n); ysfx_real *p = ysfx_find_var(fx, nm); std::vector<ysfx_real> v(n); ysfx_read_vmem(fx, (uint32_t)(*p) + a, v.data(), n); printf("%s[%u..]:", nm, a); for (unsigned i = 0; i < n; i++) printf(" %g", v[i]); printf("\n"); }
        else if (!strcmp(cmd, "save")) {
            char fn[256]; sscanf(line, "%*s %255s", fn); FILE *o = fopen(fn, "wb"); fprintf(o, "P6\n%d %d\n255\n", W, H);
            for (int i = 0; i < W * H; i++) { uint8_t *q = &px[i * 4]; fputc(q[2], o); fputc(q[1], o); fputc(q[0], o); } fclose(o);
        }
    }
    ysfx_free(fx); ysfx_config_free(cfg); return 0;
}
