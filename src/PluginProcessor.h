#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "engine.h"
#include "UpdateCheck.h"

class RoomServiceProcessor : public juce::AudioProcessor, private juce::Timer {
public:
    RoomServiceProcessor();
    ~RoomServiceProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override {}
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    void processBlock(juce::AudioBuffer<double>&, juce::MidiBuffer&) override;
    bool supportsDoublePrecisionProcessing() const override { return true; }

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 10.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    rs::Engine engine;

    // diagnostics (roomservice-debug.txt on the desktop): time spent in host notifications and state calls
    struct Diag { std::atomic<int> notifyCount { 0 }, stateCount { 0 }; std::atomic<double> notifyMs { 0 }, notifyMaxMs { 0 }, stateMs { 0 }; };
    Diag diag;
    juce::CriticalSection engineLock;            // @serialize vs audio (the @gfx thread runs unlocked, as in REAPER)
    // the instance has processed audio or shown its editor: a state arriving now is a preset (the view stays),
    // a state arriving before that is the project being loaded (everything is restored)
    void initForEditor();
    bool hasHeldState() const { return heldAny.load(); }
    std::atomic<bool> heldAny { false };
    std::atomic<bool> hasRun { false };
    const double createdMs = juce::Time::getMillisecondCounterHiRes();   // a project load sets the state right after creation

private:
    template <class Real> void process(juce::AudioBuffer<Real>& buffer);
    void syncParamsToEngine();
    void scriptAutomate(int idx, int mode);
    void scriptChanged(int idx);
    void notifyAutomate(int idx, int mode);      // message thread only
    void notifyChanged(int idx);                 // message thread only
    void timerCallback() override;               // delivers notifications the script raised on the audio thread

    std::vector<juce::RangedAudioParameter*> paramBySlider;   // index = JSFX slider number
    std::unique_ptr<std::atomic<float>[]> lastPushed;
    std::vector<char> touching;
    std::unique_ptr<std::atomic<int>[]> pending;   // per slider: 1 value, 2 touch begin, 4 touch end, 8 display only
    std::atomic<bool> pendingAny { false };
    juce::SharedResourcePointer<rs::UpdateCheck> updateCheck;   // one check for all instances
    int lastLatency = -1;
    bool prepared = false;            // guarded by engineLock
    std::vector<float> heldSer;       // guarded by engineLock
    void applyHeldState();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RoomServiceProcessor)
};
