#!/bin/bash
# Ahh (formerly Roomservice): build on the Mac and install into the plug-in folders.
# Usage (Terminal):  bash build_mac.sh
set -e
cd "$(dirname "$0")"
HERE="$(pwd)"
JUCE_COMMIT=d60b7a78030661574a615b586d9325ba7a7fa7dd   # JUCE 9.0.5

echo "== 1/5 Werkzeuge prüfen"
if ! xcode-select -p >/dev/null 2>&1; then
  echo "Die Xcode Command Line Tools fehlen. Es öffnet sich gleich ein Fenster: auf 'Installieren' klicken,"
  echo "warten bis es fertig ist, dann dieses Skript noch einmal starten."
  xcode-select --install
  exit 1
fi
CMAKE="$(command -v cmake || true)"
[ -z "$CMAKE" ] && [ -x /Applications/CMake.app/Contents/bin/cmake ] && CMAKE=/Applications/CMake.app/Contents/bin/cmake
if [ -z "$CMAKE" ]; then
  echo "CMake fehlt: von https://cmake.org/download/ die macOS-.dmg laden, CMake.app in 'Programme' ziehen,"
  echo "dann dieses Skript noch einmal starten."
  exit 1
fi
echo "   cmake: $CMAKE"

echo "== 2/5 JUCE holen (nur beim ersten Mal)"
if [ ! -d "$HERE/../juce/.git" ]; then
  git clone https://github.com/juce-framework/JUCE.git "$HERE/../juce"
fi
git -C "$HERE/../juce" fetch --quiet origin "$JUCE_COMMIT" 2>/dev/null || true
git -C "$HERE/../juce" checkout --quiet "$JUCE_COMMIT"

ARCH="$(uname -m)"   # x86_64 on Intel, arm64 on Apple Silicon: only build for this Mac (faster)
echo "== 3/5 Projekt einrichten ($ARCH)"
"$CMAKE" -S "$HERE" -B "$HERE/build" -DCMAKE_BUILD_TYPE=Release -DCMAKE_OSX_ARCHITECTURES="$ARCH"

echo "== 4/5 Bauen (dauert beim ersten Mal 5-15 Minuten)"
"$CMAKE" --build "$HERE/build" --config Release --target Roomservice_VST3 Roomservice_AU --parallel "$(sysctl -n hw.ncpu)"

echo "== 5/5 Installieren"
VST3="$HERE/build/Roomservice_artefacts/Release/VST3/Ahh.vst3"
AU="$HERE/build/Roomservice_artefacts/Release/AU/Ahh.component"
mkdir -p ~/Library/Audio/Plug-Ins/VST3 ~/Library/Audio/Plug-Ins/Components
rm -rf ~/Library/Audio/Plug-Ins/VST3/Ahh.vst3 ~/Library/Audio/Plug-Ins/Components/Ahh.component ~/Library/Audio/Plug-Ins/VST3/Roomservice.vst3 ~/Library/Audio/Plug-Ins/Components/Roomservice.component
cp -R "$VST3" ~/Library/Audio/Plug-Ins/VST3/
cp -R "$AU" ~/Library/Audio/Plug-Ins/Components/
codesign --force --deep -s - ~/Library/Audio/Plug-Ins/VST3/Ahh.vst3 >/dev/null 2>&1 || true
codesign --force --deep -s - ~/Library/Audio/Plug-Ins/Components/Ahh.component >/dev/null 2>&1 || true
killall -9 AudioComponentRegistrar >/dev/null 2>&1 || true   # AU list refresh
echo
echo "Fertig. Installiert:"
echo "  ~/Library/Audio/Plug-Ins/VST3/Ahh.vst3"
echo "  ~/Library/Audio/Plug-Ins/Components/Ahh.component"
echo "In REAPER: Options > Preferences > Plug-ins > VST > 'Re-scan', dann FX 'Ahh (dmajorsound)'."
