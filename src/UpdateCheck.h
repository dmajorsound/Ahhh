#pragma once
#include <juce_core/juce_core.h>
#include <atomic>
#include <string>

namespace rs {

// Is there a newer Ahh? Asks GitHub once per host session, in the background, and gives up quietly when there
// is no connection or no answer within a few seconds. (The same check as in OLAAF.) Nothing but the request for the
// public release list is sent.
// One object for all plug-in instances (juce::SharedResourcePointer): the thread is stopped before the last instance
// goes, so nothing of the plug-in runs after the host unloads it.
class UpdateCheck : private juce::Thread {
public:
    UpdateCheck();
    ~UpdateCheck() override;
    // 0 still asking, 1 a newer release (tag and page filled in), 2 nothing newer or no answer
    static int state(std::string* tag, std::string* url);
    // opens the release page in the browser (only pages of dmajorsound on github.com)
    static void openPage(const std::string& url);
    // "v1.2.3" / "1.2.3-beta" -> is a newer than b?
    static bool newer(const std::string& a, const std::string& b);

    // ---- update straight from GitHub (as in OLAAF) ----
    // The newer release's installer for this system: ..._mac.dmg on macOS, ..._win64.exe on Windows, never an
    // uninstaller. "" when there is none (Linux): then the release page is the way.
    static std::string assetUrl();
    // where downloads go: the folder chosen once (kept in the plug-in's settings file), else Downloads in the home folder
    static juce::File folder();
    static void setFolder(const juce::File& dir, bool save);
    // downloads the installer into folder() in the background; install: opens it when it is there
    static void downloadStart(bool install);
    // 0 not started, 1 downloading (progress 0..1, -1 = size unknown), 2 there (path), 3 failed (error)
    static int downloadState(double* progress, std::string* path, std::string* error);
    // opens a downloaded installer in the background (macOS: "Install Ahh.pkg" from the disk image, Windows: the setup)
    static void installStart(const std::string& path);
    static void reveal(const std::string& path);
    static void setAssetForTest(const std::string& url);   // (the build's self-test)
    static void stopForTest();
private:
    void run() override;
    juce::CriticalSection streamLock;
    juce::WebInputStream* stream = nullptr;
    bool mine = false;
};

} // namespace rs
