#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_dsp/juce_dsp.h>

// #include <juce_audio_basics/juce_audio_basics.h>
// #include <juce_audio_devices/juce_audio_devices.h>

class SerialMonitor;
class Body;
class Transport;
class OscillatorWrapper;
class GraphVector;

class GraphMeta {

// remains immutable and encapsulated unless explicitly accessed by the intended consumer
friend class Grapher; 

public:
    GraphMeta(std::string name, std::string type, std::vector<std::string> fields)
        : name(std::move(name)), type(std::move(type)), fields(std::move(fields)) {}
    ~GraphMeta() {}
private:
    std::string name;
    std::string type;
    std::vector<std::string> fields;
};

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent();

    // AudioAppComponent overrides
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override {}

    // Component overrides
    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.setFont(20.0f);
        g.drawText("Main", getLocalBounds(), juce::Justification::centred, true);
    }
    void resized() override {}

private:
    std::unique_ptr<SerialMonitor> serialMonitor;
    std::unique_ptr<Body> body;
    std::unique_ptr<Transport> transport;
    std::unique_ptr<OscillatorWrapper> oscillator;

    const std::vector<GraphMeta> meta;
    std::unique_ptr<GraphVector> graphVector;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
