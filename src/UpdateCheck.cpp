#include "UpdateCheck.h"
#include <mutex>
#include <vector>

namespace rs {

static const char* kApi = "https://api.github.com/repos/dmajorsound/Roomservice/releases?per_page=1";   // newest, betas included
static const char* kPages = "https://github.com/dmajorsound/Roomservice/";

static std::atomic<int> g_state { 0 };
static std::atomic<bool> g_started { false };
static std::mutex g_mu;
static std::string g_tag, g_url;

static std::vector<int> versionParts(const std::string& v) {
    std::vector<int> r;
    int cur = -1;
    for (char ch : v) {
        if (ch >= '0' && ch <= '9') cur = (cur < 0 ? 0 : (cur < 100000 ? cur * 10 : cur)) + (ch - '0');
        else if (cur >= 0) {
            r.push_back(cur);
            cur = -1;
            if (ch != '.') break;   // "1.1.0-beta": stop at the suffix
        }
    }
    if (cur >= 0) r.push_back(cur);
    while (r.size() < 3) r.push_back(0);
    return r;
}

bool UpdateCheck::newer(const std::string& a, const std::string& b) { return versionParts(a) > versionParts(b); }

// a tag is shown in the plug-in: short, and only letters, digits, dot, dash, underscore
static bool plainTag(const std::string& t) {
    if (t.empty() || t.size() > 24) return false;
    for (char c : t)
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '.' || c == '-' || c == '_')) return false;
    return true;
}

static bool ownPage(const std::string& u) {
    if (u.size() > 200 || u.compare(0, std::strlen(kPages), kPages) != 0) return false;
    for (char c : u)
        if (c <= ' ' || c == '"' || c == '\'' || c == '`' || c == '\\' || (unsigned char)c >= 127) return false;
    return true;
}

UpdateCheck::UpdateCheck() : juce::Thread("Roomservice update check") {
    if (g_started.exchange(true)) return;   // once per host session
    mine = true;
#if JUCE_LINUX
    // test hook (Linux builds are not shipped and have no HTTPS here): pretend that this release is out
    if (const char* t = std::getenv("ROOMSERVICE_TEST_UPDATE")) {
        if (plainTag(t)) { { std::lock_guard<std::mutex> l(g_mu); g_tag = t; g_url = std::string(kPages) + "releases/tag/" + t; } g_state = 1; return; }
    }
#endif
    startThread(juce::Thread::Priority::low);
}

UpdateCheck::~UpdateCheck() {
    if (!mine) return;
    signalThreadShouldExit();
    { const juce::ScopedLock l(streamLock); if (stream) stream->cancel(); }
    stopThread(10000);
    if (g_state.load() == 0) g_started = false;   // stopped before the answer: the next instance asks again
}

void UpdateCheck::run() {
    juce::String js;
    {
        juce::WebInputStream in(juce::URL(kApi), false);
        in.withExtraHeaders("Accept: application/vnd.github+json\r\nUser-Agent: Roomservice/" JucePlugin_VersionString "\r\n")
          .withConnectionTimeout(4000)
          .withNumRedirectsToFollow(3);
        { const juce::ScopedLock l(streamLock); stream = &in; }
        bool ok = !threadShouldExit() && in.connect(nullptr) && in.getStatusCode() == 200;
        juce::MemoryOutputStream body;
        const double until = juce::Time::getMillisecondCounterHiRes() + 8000.0;
        while (ok && !threadShouldExit() && !in.isExhausted() && body.getDataSize() < 2000000) {
            char buf[4096];
            const int n = in.read(buf, (int)sizeof(buf));
            if (n <= 0) break;
            body.write(buf, (size_t)n);
            if (juce::Time::getMillisecondCounterHiRes() > until) ok = false;
        }
        { const juce::ScopedLock l(streamLock); stream = nullptr; }
        if (!ok || threadShouldExit()) { if (!threadShouldExit()) g_state = 2; return; }
        js = body.toUTF8();
    }
    const juce::var v = juce::JSON::parse(js);
    const juce::var first = v.isArray() && v.size() > 0 ? v[0] : juce::var();
    const std::string tag = first["tag_name"].toString().toStdString(), url = first["html_url"].toString().toStdString();
    if (!plainTag(tag) || !newer(tag, JucePlugin_VersionString) || !ownPage(url)) { g_state = 2; return; }
    { std::lock_guard<std::mutex> l(g_mu); g_tag = tag; g_url = url; }
    g_state = 1;
}

int UpdateCheck::state(std::string* tag, std::string* url) {
    const int s = g_state.load();
    if (s == 1) {
        std::lock_guard<std::mutex> l(g_mu);
        if (tag) *tag = g_tag;
        if (url) *url = g_url;
    }
    return s;
}

void UpdateCheck::openPage(const std::string& url) {
    if (ownPage(url)) juce::URL(juce::String(url)).launchInDefaultBrowser();
}

} // namespace rs
