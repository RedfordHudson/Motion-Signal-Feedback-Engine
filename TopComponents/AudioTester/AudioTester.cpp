#include "AudioTester.h"

#include <RatioDisplay.h>
#include <BarDisplay.h>
#include <BeatDisplay.h>

#include <Transport.h>
#include <OscillatorWrapper.h>




#include <vector>
#include <cmath>
#include <numeric>

class SoftQuantizer {
public:
    SoftQuantizer()
        : out_min(*std::min_element(attractors.begin(), attractors.end())),
          out_max(*std::max_element(attractors.begin(), attractors.end()))
    {}

    ~SoftQuantizer() = default;

    float scale(float x) const {
        if (in_max - in_min == 0.0f)
            return out_min;

        float t = (x - in_min) / (in_max - in_min);
        return out_min + t * (out_max - out_min);
    }

    float quantize(float x) const {
        x = scale(x);

        float numerator = 0.0f;
        float denominator = 0.0f;

        for (float attractor : attractors) {
            float distance = std::abs(x - attractor);
            float weight = 1.0f / (std::pow(distance, strength) + epsilon);
            numerator += weight * attractor;
            denominator += weight;
        }

        return numerator / denominator;
    }

private:
    const std::vector<float> attractors { 0.0f, 1.0f, 3.0f, 5.0f };
    const float strength = 10.0f;
    const float epsilon = 1e-5f;

    const float in_min = 0.0f;
    const float in_max = 1.0f;

    float out_min;
    float out_max;
};


AudioTester::AudioTester()
    :
    transport(std::make_unique<Transport>(40,3.0f/8.0f)),
    ratioDisplay(std::make_unique<RatioDisplay>()),
    sq(std::make_unique<SoftQuantizer>()),
    barDisplay(std::make_unique<BarDisplay>(true)),
    beatDisplay(std::make_unique<BeatDisplay>(3.0f/8.0f,true)),
    oscillator(std::make_unique<OscillatorWrapper>(440.f))
{
    addAndMakeVisible(*ratioDisplay);
    addAndMakeVisible(*barDisplay);
    addAndMakeVisible(*beatDisplay);

    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels
}

AudioTester::~AudioTester() {
    shutdownAudio();
}


void AudioTester::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Draw border
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
}

void AudioTester::resized() {
    juce::FlexBox flexbox;
    flexbox.flexDirection = juce::FlexBox::Direction::column;

    for (auto* child : getChildren()) {
        flexbox.items.add(juce::FlexItem(*child).withFlex(1.0f));
    }

    flexbox.performLayout(getLocalBounds());
}


void AudioTester::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    oscillator->prepareToPlay(samplesPerBlockExpected,sampleRate);

    transport->prepareToPlay((float)sampleRate);
}

void AudioTester::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Clear the buffer
    bufferToFill.clearActiveBufferRegion();

    juce::AudioBuffer<float>& buffer = *bufferToFill.buffer;
    
    auto [beatSampleIndex, phase, cycleBeatSampleIndex, cyclePhase] = transport->processBlock(bufferToFill);

    beatDisplay->updatePhase(phase);
    barDisplay->updatePhase(transport->calculateBarPhase());

    float ratio_freq = transport->calculateBarPhase();
    ratio_freq = sq->quantize(ratio_freq);
    ratio_freq = (15.0f+ratio_freq)/20.0f;
    ratioDisplay->updateRatio(ratio_freq);
    oscillator->modulateFrequency(ratio_freq);

    float ratio_cycle = (transport->getBeatCount() % 2 == 0) ? .5f : 3.0f/8.0f;
    beatDisplay->updateRatio(ratio_cycle);
    transport->updateRatio(ratio_cycle);

    oscillator->processBlock(buffer,cycleBeatSampleIndex);
}