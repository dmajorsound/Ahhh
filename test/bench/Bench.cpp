// times @gfx frames: Expert view, Filter module, mouse held (full redraw every frame, like while dragging)
#include <juce_gui_basics/juce_gui_basics.h>
#include "engine.h"
#include "JuceGfx.h"
using namespace juce;
struct NullGfx : rs::GfxBackend {
    void rect(double, double, double, double, bool) override {} void line(double, double, double, double, bool) override {}
    void circle(double, double, double, bool, bool) override {} void arc(double, double, double, double, double, bool) override {}
    void triangle(const double*, int) override {} void roundrect(double, double, double, double, double, bool) override {}
    void gradrect(const double*, int) override {} void drawstr(const std::string&, int, double, double) override {}
    void measurestr(const std::string& s, double& w, double& h) override { w = 6.0 * s.size(); h = 12; }
    void setfont(int, const std::string*, double, int) override {} void setimgdim(int, int, int) override {}
    void blit(const double*, int) override {} void setcursor(int) override {} double getchar(double, bool) override { return 0; }
};
static int g_counts[32]; static double g_times[32];
struct TimingGfx : rs::GfxBackend {
    rs::GfxBackend& b; explicit TimingGfx(rs::GfxBackend& x) : b(x) {}
    struct T { int i; double t0; T(int k) : i(k), t0(Time::getMillisecondCounterHiRes()) {} ~T() { g_counts[i]++; g_times[i] += Time::getMillisecondCounterHiRes() - t0; } };
    void rect(double a, double c, double d, double e, bool f) override { T t(0); b.rect(a, c, d, e, f); }
    void line(double a, double c, double d, double e, bool f) override { T t(1); b.line(a, c, d, e, f); }
    void circle(double a, double c, double d, bool e, bool f) override { T t(2); b.circle(a, c, d, e, f); }
    void arc(double a, double c, double d, double e, double f, bool h) override { T t(3); b.arc(a, c, d, e, f, h); }
    void triangle(const double* p, int n) override { T t(4); b.triangle(p, n); }
    void roundrect(double a, double c, double d, double e, double f, bool h) override { T t(5); b.roundrect(a, c, d, e, f, h); }
    void gradrect(const double* p, int n) override { T t(6); b.gradrect(p, n); }
    void drawstr(const std::string& s, int f, double r, double bt) override { T t(7); b.drawstr(s, f, r, bt); }
    void measurestr(const std::string& s, double& w, double& h) override { T t(8); b.measurestr(s, w, h); }
    void setfont(int i, const std::string* f, double s, int fl) override { T t(9); b.setfont(i, f, s, fl); }
    void setimgdim(int i, int w, int h) override { T t(10); b.setimgdim(i, w, h); }
    void blit(const double* p, int n) override { T t(11); b.blit(p, n); }
    void setcursor(int i) override { b.setcursor(i); }
    double getchar(double c, bool h) override { return b.getchar(c, h); }
};
int main(int argc, char** argv) {
    ScopedJuceInitialiser_GUI gui;
    rs::Engine e; e.setSampleRate(48000); e.setBlockSize(256);
    std::vector<double> z(256, 0.0); const double* in[2] = {z.data(), z.data()}; std::vector<double> o1(256), o2(256); double* out[2] = {o1.data(), o2.data()};
    rs::TimeInfo ti; e.process(in, out, 2, 2, 256, ti);
    rs::JuceGfx gfx(*e.gen); auto* g = e.gen.get();
    static int nAuto = 0, nChanged = 0, nChangedAll = 0;
    static int modes[3] = {0, 0, 0};
    e.onAutomate = [](int, int m) { nAuto++; modes[m + 1]++; };
    e.onChanged = [](int i) { nChanged++; if (i < 0) nChangedAll++; };
    const double SC = getenv("RSSCALE") ? atof(getenv("RSSCALE")) : 1.0;
    const int W = (int)(760 * SC), H = (int)(574 * SC);
    if (SC > 1) g->v_gfx_ext_retina = SC;
    auto frame = [&](double mx, double my, int cap) { mx *= SC; my *= SC; if (SC > 1) g->v_gfx_ext_retina = SC; g->v_mouse_x = mx; g->v_mouse_y = my; g->v_mouse_cap = cap; gfx.beginFrame(W, H); e.runGfx(&gfx, W, H); gfx.endFrame(); };
    auto click = [&](double x, double y) { for (int i = 0; i < 3; i++) frame(x, y, 0); frame(x, y, 1); frame(x, y, 0); for (int i = 0; i < 5; i++) frame(x, y, 0); };
    for (int i = 0; i < 5; i++) frame(0, 0, 0);
    click(156, 17);          // Expert
    click(40, 300);          // Filter module tab
    if (getenv("RS3D")) { click(153, 52); click(240, 15); }   // 3D stage view, then away
    const double fx = argc > 1 ? atof(argv[1]) : 200, fy = argc > 2 ? atof(argv[2]) : 430;
    // measure: hold the mouse and drag across the filter graph
    double tot = 0, mx = 0; const int N = 60; nAuto = nChanged = nChangedAll = 0;
    for (int i = 0; i < N; i++) {
        const double t0 = Time::getMillisecondCounterHiRes();
        frame(fx - (getenv("RSLEFT") ? i : -i), fy, 1);
        const double dt = Time::getMillisecondCounterHiRes() - t0; tot += dt; mx = jmax(mx, dt);
    }
    frame(fx + N, fy, 0);
    std::printf("drag frames: mean %.1f ms, max %.1f ms   automate/frame %.1f  sliderchange/frame %.1f (all: %.1f)\n", tot / N, mx, nAuto / (double)N, nChanged / (double)N, nChangedAll / (double)N);
    tot = 0;
    for (int i = 0; i < N; i++) { const double t0 = Time::getMillisecondCounterHiRes(); frame(600, 500, 0); tot += Time::getMillisecondCounterHiRes() - t0; }
    std::printf("automate modes: one-shot %d, touch %d, end %d\n", modes[0], modes[1], modes[2]);
    std::printf("idle frames: mean %.1f ms\n", tot / N);
    { const double t0 = Time::getMillisecondCounterHiRes(); auto st = e.saveState(); std::printf("state: %zu floats (%.1f KB), %.2f ms\n", st.size(), st.size() * 4 / 1024.0, Time::getMillisecondCounterHiRes() - t0); }
    NullGfx ng; tot = 0;
    for (int i = 0; i < N; i++) { g->v_mouse_x = fx + i; g->v_mouse_y = fy; g->v_mouse_cap = 1; const double t0 = Time::getMillisecondCounterHiRes(); e.runGfx(&ng, W, H); tot += Time::getMillisecondCounterHiRes() - t0; }
    TimingGfx tg(gfx); for (auto& c : g_counts) c = 0; for (auto& t : g_times) t = 0;
    for (int i = 0; i < N; i++) { g->v_mouse_x = fx + i; g->v_mouse_y = fy; g->v_mouse_cap = 1; gfx.beginFrame(W, H); e.runGfx(&tg, W, H); gfx.endFrame(); }
    const char* nm[] = {"rect","line","circle","arc","triangle","roundrect","gradrect","drawstr","measurestr","setfont","setimgdim","blit"};
    for (int i = 0; i < 12; i++) if (g_counts[i]) std::printf("  %-10s %6d/frame  %7.2f ms/frame\n", nm[i], g_counts[i] / N, g_times[i] / N);
    std::printf("drag frames, script only (no drawing): mean %.1f ms\n", tot / N);
    File f("/tmp/bench.png"); f.deleteFile(); FileOutputStream fos(f); PNGImageFormat().writeImageToStream(gfx.screen(), fos);
    return 0;
}
