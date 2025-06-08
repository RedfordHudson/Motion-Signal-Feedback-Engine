#pragma once

#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_dsp/juce_dsp.h>

class SerialMonitor;
class Body;

class Transport;
class OscillatorWrapper;

class SoftQuantizer;

class GraphVector;

class RatioDisplay;
class BarDisplay;
class BeatDisplay;

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

    std::unique_ptr<SerialMonitor> serialMonitor;
    std::unique_ptr<Body> body;
    
    std::unique_ptr<Transport> transport;
    std::unique_ptr<OscillatorWrapper> oscillator;

    std::unique_ptr<SoftQuantizer> sq;

    const std::vector<GraphMeta> meta;
    std::unique_ptr<GraphVector> graphVector;

    std::unique_ptr<RatioDisplay> ratioDisplay;
    std::unique_ptr<BarDisplay> barDisplay;
    std::unique_ptr<BeatDisplay> beatDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioTester)
};
