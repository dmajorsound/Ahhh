#include "UpdateCheck.h"
#include <juce_data_structures/juce_data_structures.h>
#include <cstring>
#include <memory>
#include <mutex>
#include <vector>

namespace rs {

// (the repository is called Ahhh; if it is renamed, GitHub forwards the request)
static const char* kApi = "https://api.github.com/repos/dmajorsound/Ahhh/releases?per_page=1";   // newest, betas included
static const char* kPages = "https://github.com/dmajorsound/";   // (any repository of ours: the page survives a rename)

static std::atomic<int> g_state { 0 };
static std::atomic<bool> g_started { false };
static std::mutex g_mu;
static std::string g_tag, g_url, g_asset;

// the installers of our own releases, and nothing else
static const char* kAssets = "https://github.com/dmajorsound/Ahhh/releases/download/";
static bool ownAsset(const std::string& u) {
   #if JUCE_LINUX
    // (Linux builds are not shipped and have no HTTPS: the download itself is tried against a local test server)
    if (std::getenv("AHH_TEST_LOCAL") != nullptr && u.compare(0, 17, "http://127.0.0.1:") == 0) return true;
   #endif
    if (u.size() > 300 || u.compare(0, std::strlen(kAssets), kAssets) != 0) return false;
    for (char c : u)
        if (c <= ' ' || c == '"' || c == '\'' || c == '`' || c == '\\' || c == '?' || c == '#' || (unsigned char)c >= 127) return false;
    if (u.find("..") != std::string::npos) return false;
    return true;
}
static bool endsWith(const std::string& s, const char* e) { const size_t n = std::strlen(e); return s.size() >= n && s.compare(s.size() - n, n, e) == 0; }
// this system's installer among a release's files
static bool installerForThisSystem(const std::string& u) {
    if (!ownAsset(u)) return false;
    std::string low = u; for (char& c : low) if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
    if (low.find("uninstall") != std::string::npos) return false;
#if JUCE_MAC
    return endsWith(low, "mac.dmg");
#elif JUCE_WINDOWS
    return endsWith(low, "win64.exe");
#else
    return false;
#endif
}

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

UpdateCheck::UpdateCheck() : juce::Thread("Ahh update check") {
    if (g_started.exchange(true)) return;   // once per host session
    mine = true;
#if JUCE_LINUX
    // test hook (Linux builds are not shipped and have no HTTPS here): pretend that this release is out
    if (const char* t = std::getenv("AHH_TEST_UPDATE")) {
        if (plainTag(t)) { { std::lock_guard<std::mutex> l(g_mu); g_tag = t; g_url = std::string(kPages) + "Ahhh/releases/tag/" + t; } g_state = 1; return; }
    }
#endif
    startThread(juce::Thread::Priority::low);
}

static void stopJob();

UpdateCheck::~UpdateCheck() {
    stopJob();       // a download or an installer start still running: stopped before the plug-in goes
    if (!mine) return;
    signalThreadShouldExit();
    { const juce::ScopedLock l(streamLock); if (stream) stream->cancel(); }
    stopThread(10000);
    if (g_state.load() == 0) g_started = false;   // stopped before the answer: the next instance asks again
}

// ---------------------------------------------------------------------------------------------------------------------
// The download: one background thread, the file first as "<name>.part", renamed only when it arrived whole.
namespace {
std::mutex d_mu;
int d_state = 0;                 // 0 not started, 1 downloading, 2 there, 3 failed
double d_prog = 0.0;
std::string d_path, d_err;
juce::File d_folder;

void openInstallerNow(const juce::File& f) {
#if JUCE_MAC
    // the installer inside the disk image; no shell: every argument goes to the program as it is
    const juce::String mount = "/tmp/ahh-update";
    juce::ChildProcess att;
    if (att.start(juce::StringArray { "/usr/bin/hdiutil", "attach", "-nobrowse", "-noautoopen", "-quiet", "-mountpoint", mount, f.getFullPathName() }, 0))
        att.waitForProcessToFinish(60000);
    const juce::File pkg(mount + "/Install Ahh.pkg");
    juce::ChildProcess op;
    if (op.start(juce::StringArray { "/usr/bin/open", pkg.existsAsFile() ? pkg.getFullPathName() : f.getFullPathName() }, 0))
        op.waitForProcessToFinish(15000);
#elif JUCE_WINDOWS
    f.startAsProcess();
#else
    f.getParentDirectory().revealToUser();
#endif
}

struct Job final : juce::Thread {
    Job(std::string urlToGet, std::string fileToOpen, bool installAfter)
        : juce::Thread("Ahh update download"), url(std::move(urlToGet)), openPath(std::move(fileToOpen)), install(installAfter) { startThread(juce::Thread::Priority::low); }
    ~Job() override {
        signalThreadShouldExit();
        { const juce::ScopedLock l(lock); if (stream) stream->cancel(); }
        stopThread(70000);
    }
    void fail(const juce::File& part, const std::string& why) {
        part.deleteFile();
        std::lock_guard<std::mutex> l(d_mu); d_state = 3; d_err = why;
    }
    void run() override {
        if (url.empty()) { openInstallerNow(juce::File(openPath)); return; }   // "Install now" for a file that is there
        juce::File dir; { std::lock_guard<std::mutex> l(d_mu); dir = d_folder; }
        if (dir == juce::File()) dir = rs::UpdateCheck::folder();
        const juce::String name = juce::String(url).fromLastOccurrenceOf("/", false, false);
        const juce::File target = dir.getChildFile(juce::File::createLegalFileName(name)), part = dir.getChildFile(target.getFileName() + ".part");
        if (name.isEmpty() || !dir.createDirectory()) { fail(part, "the folder cannot be written"); return; }
        part.deleteFile();
        juce::int64 total = -1, done = 0;
        bool whole = false; std::string why = "no connection";
        {
            juce::WebInputStream in(juce::URL(juce::String(url)), false);
            in.withExtraHeaders("User-Agent: Ahh/" JucePlugin_VersionString "\r\n")
              .withConnectionTimeout(30000)       // also: gives up when nothing arrives for 30 s
              .withNumRedirectsToFollow(5);       // GitHub hands the file out from objects.githubusercontent.com
            { const juce::ScopedLock l(lock); stream = &in; }
            if (!threadShouldExit() && in.connect(nullptr)) {
                const int code = in.getStatusCode();
                if (code != 200) why = "the server answered " + std::to_string(code);
                else if (auto out = part.createOutputStream(0x8000)) {
                    total = in.getTotalLength();
                    juce::HeapBlock<char> buf(0x8000);
                    why = "the connection broke off";
                    while (!threadShouldExit() && !in.isExhausted() && !in.isError()) {
                        const int n = in.read(buf.get(), 0x8000);
                        if (n <= 0) break;
                        if (!out->write(buf.get(), (size_t)n)) { why = "the disk is full or the folder cannot be written"; done = -1; break; }
                        done += n;
                        { std::lock_guard<std::mutex> l(d_mu); d_prog = total > 0 ? juce::jlimit(0.0, 1.0, (double)done / (double)total) : -1.0; }
                        if (total > 0 && done >= total) break;
                    }
                    out->flush();
                    out.reset();
                    // whole: exactly as long as the server said (without a length: an installer, not an error page)
                    whole = done > 0 && !in.isError() && (total > 0 ? done == total && part.getSize() == total : done > 500000);
                } else why = "the folder cannot be written";
            }
            { const juce::ScopedLock l(lock); stream = nullptr; }
        }
        if (threadShouldExit()) { part.deleteFile(); std::lock_guard<std::mutex> l(d_mu); d_state = 0; return; }
        if (!whole) { fail(part, why); return; }
        target.deleteFile();
        if (!part.moveFileTo(target)) { fail(part, "the file cannot be saved"); return; }
        { std::lock_guard<std::mutex> l(d_mu); d_state = 2; d_prog = 1.0; d_path = target.getFullPathName().toStdString(); d_err.clear(); }
        if (install && !threadShouldExit()) openInstallerNow(target);
    }
    const std::string url, openPath;
    const bool install;
    juce::CriticalSection lock;
    juce::WebInputStream* stream = nullptr;
};
std::unique_ptr<Job> d_job;     // (message thread and the object's destructor only)

juce::PropertiesFile::Options settingsFile() {
    juce::PropertiesFile::Options o;
    o.applicationName = "Ahh"; o.folderName = "dmajorsound"; o.filenameSuffix = ".settings"; o.osxLibrarySubFolder = "Application Support";
    return o;
}
} // namespace

static void stopJob() { d_job.reset(); }
void UpdateCheck::stopForTest() { stopJob(); }

std::string UpdateCheck::assetUrl() { std::lock_guard<std::mutex> l(g_mu); return g_asset; }
void UpdateCheck::setAssetForTest(const std::string& url) { std::lock_guard<std::mutex> l(g_mu); g_asset = ownAsset(url) ? url : std::string(); }

juce::File UpdateCheck::folder() {
    { std::lock_guard<std::mutex> l(d_mu); if (d_folder != juce::File()) return d_folder; }
    juce::File dir;
    {
        juce::PropertiesFile pf(settingsFile());
        const juce::String kept = pf.getValue("updateFolder");
        if (kept.isNotEmpty() && juce::File::isAbsolutePath(kept) && juce::File(kept).isDirectory()) dir = juce::File(kept);
    }
    if (dir == juce::File()) dir = juce::File::getSpecialLocation(juce::File::userHomeDirectory).getChildFile("Downloads");
    std::lock_guard<std::mutex> l(d_mu); d_folder = dir; return dir;
}

void UpdateCheck::setFolder(const juce::File& dir, bool save) {
    { std::lock_guard<std::mutex> l(d_mu); d_folder = dir; }
    if (save) { juce::PropertiesFile pf(settingsFile()); pf.setValue("updateFolder", dir.getFullPathName()); pf.saveIfNeeded(); }
}

void UpdateCheck::downloadStart(bool install) {
    const std::string url = assetUrl();
    if (url.empty()) return;
    { std::lock_guard<std::mutex> l(d_mu); if (d_state == 1) return; d_state = 1; d_prog = 0.0; d_err.clear(); d_path.clear(); }
    folder();
    d_job.reset();
    d_job = std::make_unique<Job>(url, std::string(), install);
}

int UpdateCheck::downloadState(double* progress, std::string* path, std::string* error) {
    std::lock_guard<std::mutex> l(d_mu);
    if (progress) *progress = d_prog;
    if (path) *path = d_path;
    if (error) *error = d_err;
    return d_state;
}

void UpdateCheck::installStart(const std::string& path) {
    { std::lock_guard<std::mutex> l(d_mu); if (d_state == 1) return; }
    d_job.reset();
    d_job = std::make_unique<Job>(std::string(), path, true);
}

void UpdateCheck::reveal(const std::string& path) { juce::File(path).revealToUser(); }

void UpdateCheck::run() {
    juce::String js;
    {
        juce::WebInputStream in(juce::URL(kApi), false);
        in.withExtraHeaders("Accept: application/vnd.github+json\r\nUser-Agent: Ahh/" JucePlugin_VersionString "\r\n")
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
    std::string asset;
    if (const auto* files = first["assets"].getArray())
        for (const auto& f : *files) {
            const std::string u = f["browser_download_url"].toString().toStdString();
            if (installerForThisSystem(u)) { asset = u; break; }
        }
    { std::lock_guard<std::mutex> l(g_mu); g_tag = tag; g_url = url; g_asset = asset; }
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
