#include "JuceGfx.h"
#include "RsData.h"

namespace rs {

// A script can hand over any number (a division by zero while a value is not set yet, a huge zoom): nothing that is
// not a sane pixel coordinate reaches the rasterizer.
static inline bool fin(double v) { return std::isfinite(v) && std::fabs(v) < 1.0e6; }
static inline int ti(double v) { return fin(v) ? (int)v : 0; }   // LICE takes ints: truncation like the C cast

static const char kCheck[] = "\xE2\x9C\x93";   // U+2713

juce::Typeface::Ptr JuceGfx::typeface(bool bold) {
    static juce::Typeface::Ptr regular = juce::Typeface::createSystemTypefaceFor(RsData::ArimoRegular_ttf, (size_t)RsData::ArimoRegular_ttfSize);
    static juce::Typeface::Ptr strong = juce::Typeface::createSystemTypefaceFor(RsData::ArimoBold_ttf, (size_t)RsData::ArimoBold_ttfSize);
    return bold ? strong : regular;
}

void JuceGfx::takeDirty(juce::RectangleList<int>& out) {
    out.clear();
    if (!screenImg.isValid()) return;
    const int W = screenImg.getWidth(), H = screenImg.getHeight();
    if (!shownImg.isValid() || shownImg.getWidth() != W || shownImg.getHeight() != H) {
        shownImg = screenImg.createCopy();
        out.add(0, 0, W, H);
        return;
    }
    juce::Image::BitmapData a(screenImg, juce::Image::BitmapData::readOnly), b(shownImg, juce::Image::BitmapData::readWrite);
    int top = -1, bottom = 0, minX = 0, maxX = 0, gap = 0;
    auto flush = [&] { if (top >= 0) out.addWithoutMerging({minX, top, maxX - minX + 1, bottom - top + 1}); top = -1; };
    for (int y = 0; y < H; y++) {
        const juce::uint32* pa = (const juce::uint32*)a.getLinePointer(y);
        juce::uint32* pb = (juce::uint32*)b.getLinePointer(y);
        if (std::memcmp(pa, pb, (size_t)W * 4) != 0) {
            int x0 = 0, x1 = W - 1;
            while (x0 < W && pa[x0] == pb[x0]) x0++;
            while (x1 > x0 && pa[x1] == pb[x1]) x1--;
            std::memcpy(pb + x0, pa + x0, (size_t)(x1 - x0 + 1) * 4);
            if (top < 0) { top = y; minX = x0; maxX = x1; } else { minX = juce::jmin(minX, x0); maxX = juce::jmax(maxX, x1); }
            bottom = y; gap = 0;
        } else if (top >= 0 && ++gap > 12) flush();   // rows apart: their own rectangle
    }
    flush();
}

void JuceGfx::beginFrame(int w, int h) {
    if (!screenImg.isValid() || screenImg.getWidth() != w || screenImg.getHeight() != h) {
        juce::Image n(juce::Image::ARGB, juce::jmax(1, w), juce::jmax(1, h), true, juce::SoftwareImageType());
        if (screenImg.isValid()) { juce::Graphics cg(n); cg.drawImageAt(screenImg, 0, 0); }
        screenImg = n;
        if (gDest == -1) { g.reset(); gDest = -2; }
    }
    // gfx_clear > -1: clear the screen to that color (packed RGB) before @gfx
    const double c = rt.v_gfx_clear;
    if (c > -1.0) {
        const int ic = (int)c;
        juce::Graphics cg(screenImg);
        cg.fillAll(juce::Colour((juce::uint8)(ic & 255), (juce::uint8)((ic >> 8) & 255), (juce::uint8)((ic >> 16) & 255)));
    }
}

void JuceGfx::endFrame() { g.reset(); gDest = -2; }

juce::Image* JuceGfx::destImage() {
    const int d = (int)rt.v_gfx_dest;
    if (d < 0) return &screenImg;
    auto it = images.find(d);
    if (it == images.end() || !it->second.isValid()) return nullptr;
    return &it->second;
}

juce::Graphics& JuceGfx::G() {
    int d = (int)rt.v_gfx_dest;
    if (d >= 0 && images.find(d) == images.end()) d = -1000;   // no such image: draw nowhere
    if (!g || d != gDest) {
        g.reset();
        static juce::Image dummy(juce::Image::ARGB, 1, 1, true, juce::SoftwareImageType());
        juce::Image* im = d == -1000 ? &dummy : destImage();
        if (!im) im = &dummy;
        g = std::make_unique<juce::Graphics>(*im);
        g->setImageResamplingQuality(juce::Graphics::mediumResamplingQuality);
        gDest = d;
    }
    return *g;
}

juce::Colour JuceGfx::colour() const {
    auto cl = [](double v) { return (float)juce::jlimit(0.0, 1.0, v); };
    return juce::Colour::fromFloatRGBA(cl(rt.v_gfx_r), cl(rt.v_gfx_g), cl(rt.v_gfx_b), cl(rt.v_gfx_a));
}

void JuceGfx::rect(double x, double y, double w, double h, bool filled) {
    if (!(fin(x) && fin(y) && fin(w) && fin(h))) return;
    auto& gr = G(); gr.setColour(colour());
    const int ix = ti(x), iy = ti(y), iw = ti(w), ih = ti(h);
    if (iw <= 0 || ih <= 0) return;
    if (filled) gr.fillRect(ix, iy, iw, ih); else gr.drawRect(ix, iy, iw, ih, 1);
}

void JuceGfx::line(double x1, double y1, double x2, double y2, bool) {
    if (!(fin(x1) && fin(y1) && fin(x2) && fin(y2))) return;
    auto& gr = G(); gr.setColour(colour());
    // straight lines on whole pixels (grids, ticks, borders): a pixel rectangle, much cheaper than a stroked path
    if (x1 == std::floor(x1) && y1 == std::floor(y1) && x2 == std::floor(x2) && y2 == std::floor(y2) && (x1 == x2 || y1 == y2)) {
        const int ax = (int)juce::jmin(x1, x2), ay = (int)juce::jmin(y1, y2);
        gr.fillRect(ax, ay, (int)std::fabs(x2 - x1) + 1, (int)std::fabs(y2 - y1) + 1);
        return;
    }
    // other lines: anti-aliased 1 px (Xiaolin Wu, like LICE) straight into the pixels - a stroked JUCE path per line is
    // far too slow for the thousands of curve/spectrum segments per frame
    juce::Image* im = destImage();
    if (!im || !im->isValid() || inClip) { gr.drawLine((float)x1 + 0.5f, (float)y1 + 0.5f, (float)x2 + 0.5f, (float)y2 + 0.5f, 1.0f); return; }
    if (!(std::isfinite(x1) && std::isfinite(y1) && std::isfinite(x2) && std::isfinite(y2))) return;
    const int W = im->getWidth(), H = im->getHeight();
    if (std::fabs(x1) > 1e5 || std::fabs(x2) > 1e5 || std::fabs(y1) > 1e5 || std::fabs(y2) > 1e5) return;
    const juce::Colour col = colour();
    const float ca = col.getFloatAlpha();
    juce::Image::BitmapData bd(*im, juce::Image::BitmapData::readWrite);
    auto plot = [&](int px, int py, float cov) {
        if (px < 0 || py < 0 || px >= W || py >= H || cov <= 0.0f) return;
        juce::PixelARGB src = col.withAlpha(juce::jlimit(0.0f, 1.0f, ca * cov)).getPixelARGB();
        ((juce::PixelARGB*)bd.getPixelPointer(px, py))->blend(src);
    };
    double ax = x1, ay = y1, bx = x2, by = y2;
    const bool steep = std::fabs(by - ay) > std::fabs(bx - ax);
    if (steep) { std::swap(ax, ay); std::swap(bx, by); }
    if (ax > bx) { std::swap(ax, bx); std::swap(ay, by); }
    const double dx = bx - ax, dy = by - ay, grad = dx == 0.0 ? 1.0 : dy / dx;
    const int xs = (int)std::floor(ax + 0.5), xe = (int)std::floor(bx + 0.5);
    double yy = ay + grad * (xs - ax);
    for (int x = xs; x <= xe; x++, yy += grad) {
        const int iy = (int)std::floor(yy); const float f = (float)(yy - iy);
        if (steep) { plot(iy, x, 1.0f - f); plot(iy + 1, x, f); }
        else { plot(x, iy, 1.0f - f); plot(x, iy + 1, f); }
    }
}

void JuceGfx::circle(double x, double y, double r, bool fill, bool) {
    if (!(fin(x) && fin(y) && fin(r)) || r < 0 || r > 1.0e5) return;
    auto& gr = G(); gr.setColour(colour());
    const float cx = (float)x + 0.5f, cy = (float)y + 0.5f, rr = (float)r;
    if (fill) gr.fillEllipse(cx - rr - 0.5f, cy - rr - 0.5f, 2 * rr + 1, 2 * rr + 1);
    else gr.drawEllipse(cx - rr, cy - rr, 2 * rr, 2 * rr, 1.0f);
}

void JuceGfx::arc(double x, double y, double r, double a1, double a2, bool) {
    if (!(fin(x) && fin(y) && fin(r) && fin(a1) && fin(a2)) || r < 0 || r > 1.0e5) return;
    auto& gr = G(); gr.setColour(colour());
    juce::Path p;
    p.addCentredArc((float)x + 0.5f, (float)y + 0.5f, (float)r, (float)r, 0.0f, (float)a1, (float)a2, true);
    gr.strokePath(p, juce::PathStrokeType(1.0f));
}

void JuceGfx::triangle(const double* xy, int npts) {
    if (npts < 3) return;
    for (int i = 0; i < 2 * npts; i++) if (!fin(xy[i])) return;
    auto& gr = G(); gr.setColour(colour());
    juce::Path p;
    p.startNewSubPath((float)xy[0] + 0.5f, (float)xy[1] + 0.5f);
    for (int i = 1; i < npts; i++) p.lineTo((float)xy[2 * i] + 0.5f, (float)xy[2 * i + 1] + 0.5f);
    p.closeSubPath();
    gr.fillPath(p);
}

void JuceGfx::roundrect(double x, double y, double w, double h, double radius, bool) {
    if (!(fin(x) && fin(y) && fin(w) && fin(h) && fin(radius)) || w <= 0 || h <= 0) return;
    auto& gr = G(); gr.setColour(colour());
    gr.drawRoundedRectangle((float)ti(x) + 0.5f, (float)ti(y) + 0.5f, (float)ti(w), (float)ti(h), (float)radius, 1.0f);
}

void JuceGfx::gradrect(const double* p, int n) {
    juce::Image* im = destImage();
    if (!im || n < 8) return;
    G();   // make sure gfx_dest is valid
    for (int i = 0; i < n; i++) if (!std::isfinite(p[i])) return;
    if (!(fin(p[0]) && fin(p[1]) && fin(p[2]) && fin(p[3]))) return;
    const int x0 = ti(p[0]), y0 = ti(p[1]);
    // only the part inside the image is walked (a huge width or height must not loop for seconds)
    const int w = juce::jmin(ti(p[2]), im->getWidth() - x0), h = juce::jmin(ti(p[3]), im->getHeight() - y0);
    double d[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 8 && 8 + i < n; i++) d[i] = p[8 + i];
    const int W = im->getWidth(), H = im->getHeight();
    juce::Image::BitmapData bd(*im, juce::Image::BitmapData::readWrite);
    for (int j = juce::jmax(0, -y0); j < h; j++) {
        const int py = y0 + j; if (py < 0 || py >= H) continue;
        for (int i = juce::jmax(0, -x0); i < w; i++) {
            const int px = x0 + i; if (px < 0 || px >= W) continue;
            auto cl = [](double v) { return v < 0 ? 0.0 : (v > 1 ? 1.0 : v); };
            const double r = cl(p[4] + i * d[0] + j * d[4]), gg = cl(p[5] + i * d[1] + j * d[5]),
                         b = cl(p[6] + i * d[2] + j * d[6]), a = cl(p[7] + i * d[3] + j * d[7]);
            juce::PixelARGB* px_ = (juce::PixelARGB*)bd.getPixelPointer(px, py);
            juce::PixelARGB src; src.setARGB((juce::uint8)(a * 255 + 0.5), (juce::uint8)(r * 255 + 0.5), (juce::uint8)(gg * 255 + 0.5), (juce::uint8)(b * 255 + 0.5));
            src.premultiply();
            px_->blend(src);
        }
    }
}

const juce::Font& JuceGfx::font() {
    if (!fonts[curFont].set) {
        fonts[curFont].font = juce::Font(juce::FontOptions(typeface(false)).withHeight(13.0f));
        fonts[curFont].key = "r|13";
        fonts[curFont].bold = false;
        fonts[curFont].set = true;
    }
    return fonts[curFont].font;
}

float JuceGfx::plainWidth(const juce::Font& f, const std::string& s) const {
    return s.empty() ? 0.0f : juce::GlyphArrangement::getStringWidth(f, juce::String::fromUTF8(s.c_str()));
}

// width of the drawn check mark, in units of the font height (the em is height / 1.117 for Arial metrics)
static const float kCheckWidth = 0.72f;

float JuceGfx::textWidth(const std::string& s) {
    font();
    std::string k = fonts[curFont].key; k += '\x01'; k += s;
    auto it = widthCache.find(k);
    if (it != widthCache.end()) return it->second;
    if (widthCache.size() > 50000) widthCache.clear();
    const juce::Font& f = fonts[curFont].font;
    float w = 0.0f;
    size_t pos = 0;
    for (;;) {
        const size_t c = s.find(kCheck, pos);
        w += plainWidth(f, s.substr(pos, c == std::string::npos ? std::string::npos : c - pos));
        if (c == std::string::npos) break;
        w += kCheckWidth * f.getHeight();
        pos = c + 3;
    }
    widthCache.emplace(std::move(k), w);
    return w;
}

// draws s at (0, 0) of tg: text runs in the embedded font, U+2713 as a stroked path
void JuceGfx::drawRuns(juce::Graphics& tg, const juce::Font& f, bool bold, const std::string& s, float th) {
    tg.setFont(f);
    float x = 0.0f;
    size_t pos = 0;
    for (;;) {
        const size_t c = s.find(kCheck, pos);
        const std::string part = s.substr(pos, c == std::string::npos ? std::string::npos : c - pos);
        if (!part.empty()) {
            const float w = plainWidth(f, part);
            tg.drawText(juce::String::fromUTF8(part.c_str()), juce::Rectangle<float>(x, 0.0f, w + 4, th), juce::Justification::topLeft, false);
            x += w;
        }
        if (c == std::string::npos) break;
        const float em = th / 1.117f, base = th * 0.81f, cw = kCheckWidth * th;
        juce::Path p;
        p.startNewSubPath(x + cw * 0.12f, base - em * 0.30f);
        p.lineTo(x + cw * 0.40f, base - em * 0.03f);
        p.lineTo(x + cw * 0.90f, base - em * 0.66f);
        tg.strokePath(p, juce::PathStrokeType(em * (bold ? 0.13f : 0.09f), juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
        x += cw;
        pos = c + 3;
    }
}

void JuceGfx::setfont(int idx, const std::string* face, double sz, int flags) {
    if (idx < 0 || idx > 16) idx = 0;
    curFont = idx;
    if (face) {   // the face name is not used: every text is set in the embedded font
        bool bold = false, underline = false;
        for (int s = 0; s < 32; s += 8) {
            const int ch = (flags >> s) & 255;
            if (ch == 'b') bold = true;
            if (ch == 'u') underline = true;
        }
        const float h = (float)juce::jlimit(1.0, 2000.0, std::isfinite(sz) ? sz : 13.0);
        std::string key = std::string(bold ? "b" : "r") + (underline ? "u|" : "|") + std::to_string(h);
        auto it = fontCache.find(key);
        if (it == fontCache.end())
            it = fontCache.emplace(key, juce::Font(juce::FontOptions(typeface(bold)).withHeight(h).withUnderline(underline))).first;
        fonts[idx].font = it->second;
        fonts[idx].key = key;
        fonts[idx].bold = bold;
        fonts[idx].set = true;
    }
    rt.v_gfx_texth = font().getHeight();
}

void JuceGfx::measurestr(const std::string& s, double& w, double& h) {
    w = textWidth(s);
    h = font().getHeight();
}

void JuceGfx::drawstr(const std::string& s, int flags, double right, double bottom) {
    const juce::Font& f = font();
    const float tw = textWidth(s), th = f.getHeight();
    auto sane = [](double v) { return std::isfinite(v) && std::fabs(v) < 1.0e6; };
    if (!sane(rt.v_gfx_x) || !sane(rt.v_gfx_y)) return;
    float x = (float)rt.v_gfx_x, y = (float)rt.v_gfx_y;
    const double ox = rt.v_gfx_x, oy = rt.v_gfx_y;
    bool clip = false;
    float bw = 0, bh = 0;
    if (flags != 0 && (right > rt.v_gfx_x || bottom > rt.v_gfx_y)) {
        bw = (float)(right - rt.v_gfx_x); bh = (float)(bottom - rt.v_gfx_y);
        if (flags & 1) x += (bw - tw) * 0.5f; else if (flags & 2) x += bw - tw;
        if (flags & 4) y += (bh - th) * 0.5f; else if (flags & 8) y += bh - th;
        clip = !(flags & 256);
    }
    rt.v_gfx_x = x + tw;
    if (s.empty() || tw <= 0.0f) return;
    // cached sprite: text rendered once per font / colour / string, drawn at whole pixels (as LICE does)
    const juce::Colour col = colour();
    std::string key = fonts[curFont].key; key += '\x01'; key += std::to_string(col.getARGB()); key += '\x01'; key += s;
    auto it = textCache.find(key);
    if (it == textCache.end()) {
        if (textCache.size() > 4000) textCache.clear();
        const int iw = (int)std::ceil(tw) + 4, ih = (int)std::ceil(th) + 2;
        juce::Image im(juce::Image::ARGB, juce::jmax(1, iw), juce::jmax(1, ih), true, juce::SoftwareImageType());
        {
            juce::Graphics tg(im);
            tg.setColour(col);
            drawRuns(tg, f, fonts[curFont].bold, s, th);
        }
        it = textCache.emplace(std::move(key), im).first;
    }
    auto& gr = G();
    const int ix = (int)std::floor(x + 0.5f), iy = (int)std::floor(y + 0.5f);
    if (clip) {
        juce::Graphics::ScopedSaveState ss(gr);
        gr.reduceClipRegion(juce::Rectangle<int>(ti(ox), ti(oy), ti(bw), ti(bh)));
        gr.setOpacity(1.0f);
        gr.drawImageAt(it->second, ix, iy);
    } else {
        gr.setOpacity(1.0f);
        gr.drawImageAt(it->second, ix, iy);
    }
}

void JuceGfx::setimgdim(int img, int w, int h) {
    if (img < 0 || img > 1023) return;
    if (gDest == img) { g.reset(); gDest = -2; }
    if (w <= 0 || h <= 0) { images.erase(img); return; }
    { auto it = images.find(img);   // same size: the image stays as it is, like LICE's resize (no allocation per frame)
      if (it != images.end() && it->second.isValid() && it->second.getWidth() == juce::jmin(w, 8192) && it->second.getHeight() == juce::jmin(h, 8192)) return; }
    images[img] = juce::Image(juce::Image::ARGB, juce::jmin(w, 8192), juce::jmin(h, 8192), true, juce::SoftwareImageType());
}

void JuceGfx::blit(const double* p, int n) {
    const int src = (int)p[0];
    const juce::Image* si = nullptr;
    if (src == -1) si = &screenImg;
    else { auto it = images.find(src); if (it != images.end()) si = &it->second; }
    if (!si || !si->isValid()) return;
    const double scale = n > 1 ? p[1] : 1.0;
    double sx = 0, sy = 0, sw = si->getWidth(), sh = si->getHeight();
    if (n >= 7) { sx = p[3]; sy = p[4]; sw = p[5]; sh = p[6]; }
    double dx = rt.v_gfx_x, dy = rt.v_gfx_y, dw = sw * scale, dh = sh * scale;
    if (n >= 11) { dx = p[7]; dy = p[8]; dw = p[9]; dh = p[10]; }
    if (!(fin(sx) && fin(sy) && fin(sw) && fin(sh) && fin(dx) && fin(dy) && fin(dw) && fin(dh))) return;
    if (sw <= 0 || sh <= 0 || dw <= 0 || dh <= 0) return;
    if ((int)rt.v_gfx_dest == src) return;   // LICE ignores a blit onto itself
    auto& gr = G();
    gr.setOpacity((float)juce::jlimit(0.0, 1.0, rt.v_gfx_a));
    gr.drawImage(*si, ti(dx), ti(dy), ti(dw), ti(dh), ti(sx), ti(sy), ti(sw), ti(sh), false);
    gr.setOpacity(1.0f);
}

double JuceGfx::getchar(double c, bool hasArg) {
    if (!hasArg) {
        if (keyQueue.empty()) return 0;
        const int k = keyQueue.front(); keyQueue.pop_front(); return k;
    }
    const int ic = (int)c;
    if (ic == 65536) return (focused && mouseInside) ? 15.0 : 4.0;
    return isKeyDown && isKeyDown(ic) ? 1.0 : 0.0;
}

} // namespace rs
