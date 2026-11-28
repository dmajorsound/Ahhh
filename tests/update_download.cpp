// Run by the GitHub build on macOS and Windows: downloads a released installer the way the update note in the
// footer does (same code), and checks that it arrived whole.
//   ahh_update_test <release asset URL> <folder>
#include "../src/UpdateCheck.h"
#include <cstdio>

int main(int argc, char** argv) {
    if (argc < 3) { std::fprintf(stderr, "usage: ahh_update_test <url> <folder>\n"); return 2; }
    rs::UpdateCheck::setFolder(juce::File(juce::String::fromUTF8(argv[2])), false);
    rs::UpdateCheck::setAssetForTest(argv[1]);
    if (rs::UpdateCheck::assetUrl().empty()) { std::fprintf(stderr, "not one of our release files: %s\n", argv[1]); return 2; }
    rs::UpdateCheck::downloadStart(false);
    double prog = 0; std::string path, err; int st = 1;
    for (int i = 0; i < 1800 && (st = rs::UpdateCheck::downloadState(&prog, &path, &err)) == 1; i++) juce::Thread::sleep(100);
    rs::UpdateCheck::stopForTest();
    if (st != 2) { std::fprintf(stderr, "download failed (state %d): %s\n", st, err.c_str()); return 1; }
    const juce::File f(path);
    const long long size = (long long)f.getSize();
    std::printf("downloaded %s (%lld bytes)\n", path.c_str(), size);
    if (juce::File(path + ".part").exists()) { std::fprintf(stderr, "the .part file is still there\n"); return 1; }
    return size > 500000 ? 0 : 1;   // an installer, not an error page
}
