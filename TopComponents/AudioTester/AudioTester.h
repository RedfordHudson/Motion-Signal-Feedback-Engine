#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_dsp/juce_dsp.h>

class Transport;
class OscillatorWrapper;

class SoftQuantizer;

class RatioDisplay;
class BarDisplay;
class BeatDisplay;

class AudioTester : public juce::AudioAppComponent
{
public:
    AudioTester();
    ~AudioTester();

    // AudioAppComponent overrides
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override {}

    // Component overrides
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    std::unique_ptr<Transport> transport;
    std::unique_ptr<OscillatorWrapper> oscillator;

    std::unique_ptr<SoftQuantizer> sq;

    std::unique_ptr<RatioDisplay> ratioDisplay;
    std::unique_ptr<BarDisplay> barDisplay;
    std::unique_ptr<BeatDisplay> beatDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTester)
};
