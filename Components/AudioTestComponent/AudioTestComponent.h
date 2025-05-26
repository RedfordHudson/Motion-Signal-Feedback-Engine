#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>

// #include <juce_audio_basics/juce_audio_basics.h>
// #include <juce_audio_devices/juce_audio_devices.h>

class SerialSimulator;
class Body;
class Transport;
class OscillatorWrapper;
class GraphVector;

class AudioTestComponent : public juce::AudioAppComponent
{
public:
    AudioTestComponent();
    ~AudioTestComponent();

    // AudioAppComponent overrides
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override {}

    // Component overrides
    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.setFont(20.0f);
        g.drawText("Audio Test", getLocalBounds(), juce::Justification::centred, true);
    }
    void resized() override {}

private:
    std::unique_ptr<SerialSimulator> serialSimulator;
    std::unique_ptr<Body> body;

    juce::CriticalSection bodyLock;
    std::function<void()> onBodyUpdated;

    std::unique_ptr<Transport> transport;
    std::unique_ptr<OscillatorWrapper> oscillator;
    std::unique_ptr<GraphVector> graphVector;

    float flexValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTestComponent)
};
