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
private:
    void run() override;
    juce::CriticalSection streamLock;
    juce::WebInputStream* stream = nullptr;
    bool mine = false;
};

} // namespace rs
