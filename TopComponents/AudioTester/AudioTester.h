#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_dsp/juce_dsp.h>

class FrequencyDisplay;
class BarDisplay;
class BeatDisplay;

class Transport;
class OscillatorWrapper;

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

    std::unique_ptr<FrequencyDisplay> frequencyDisplay;
    std::unique_ptr<BarDisplay> barDisplay;
    std::unique_ptr<BeatDisplay> beatDisplay;

    std::unique_ptr<Transport> transport;
    std::unique_ptr<OscillatorWrapper> oscillator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTester)
};
