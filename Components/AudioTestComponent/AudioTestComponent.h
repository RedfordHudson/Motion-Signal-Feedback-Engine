#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

// #include <juce_audio_basics/juce_audio_basics.h>
// #include <juce_audio_devices/juce_audio_devices.h>

class AudioTestComponent : public juce::AudioAppComponent
{
public:
    AudioTestComponent();
    ~AudioTestComponent() override;

    // AudioAppComponent overrides
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // Component overrides
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTestComponent)
};
