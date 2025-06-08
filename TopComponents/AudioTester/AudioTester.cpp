#include "AudioTester.h"

#include <SerialMonitor.h>
#include <HumanWare.h>

#include <Transport.h>
#include <OscillatorWrapper.h>

#include <GraphVector.h>

#include <RatioDisplay.h>
#include <BarDisplay.h>
#include <BeatDisplay.h>

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
    serialMonitor(std::make_unique<SerialMonitor>("monitor",6)),
    body(std::make_unique<Body>()),
    transport(std::make_unique<Transport>(40,3.0f/8.0f)),
    sq(std::make_unique<SoftQuantizer>()),
    meta({
        GraphMeta("gyro", "sensor", {"x", "y", "z"}),
        GraphMeta("transport", "rhythmic", {"cyclePhase"}),
        GraphMeta("cycle ratio", "parameter", {"gyro_y","ratio_cycle"}),
        GraphMeta("frequency ratio", "parameter", {"gyro_x","ratio_freq"})
    }),
    graphVector(std::make_unique<GraphVector>(meta)),
    ratioDisplay(std::make_unique<RatioDisplay>()),
    barDisplay(std::make_unique<BarDisplay>(true)),
    beatDisplay(std::make_unique<BeatDisplay>(3.0f/8.0f,true)),
    oscillator(std::make_unique<OscillatorWrapper>(440.f))
{

    addAndMakeVisible(*graphVector);

    addAndMakeVisible(*ratioDisplay);
    addAndMakeVisible(*barDisplay);
    addAndMakeVisible(*beatDisplay);

    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels
    
    serialMonitor->setCallback([this](const std::vector<float> sample) {
        juce::MessageManager::callAsync([this, sample] {
            body->processSample(sample);
        });
    });

    serialMonitor->start();
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
    // juce::FlexBox flexbox;
    // flexbox.flexDirection = juce::FlexBox::Direction::column;

    // for (auto* child : getChildren()) {
    //     flexbox.items.add(juce::FlexItem(*child).withFlex(1.0f));
    // }

    // flexbox.performLayout(getLocalBounds());

    auto bounds = getLocalBounds();

    // Split the main bounds into two columns
    auto leftColumn = bounds.removeFromLeft(bounds.getWidth() / 2);
    auto rightColumn = bounds; // Remaining half

    // Layout left column (graphVector fills this area)
    if (graphVector)
        graphVector->setBounds(leftColumn);

    // Layout right column vertically stacked
    int componentHeight = rightColumn.getHeight() / 3;

    if (ratioDisplay)
        ratioDisplay->setBounds(rightColumn.removeFromTop(componentHeight));

    if (barDisplay)
        barDisplay->setBounds(rightColumn.removeFromTop(componentHeight));

    if (beatDisplay)
        beatDisplay->setBounds(rightColumn);
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

    const float gyro_y = body->getChild("hand")->getChild("gyro")->getValue("y") / 17000;
    float ratio_cycle = (gyro_y > .5) ? 3.0f : 4.0f;
    ratio_cycle /= 8.0f;

    // float ratio_cycle = (transport->getBeatCount() % 2 == 0) ? .5f : 3.0f/8.0f;
    beatDisplay->updateRatio(ratio_cycle);
    transport->updateRatio(ratio_cycle);

    const float gyro_x = body->getChild("hand")->getChild("gyro")->getValue("x") / 17000;

    // float ratio_freq = transport->calculateBarPhase();
    float ratio_freq = sq->quantize(gyro_x);
    ratio_freq = (15.0f+ratio_freq)/20.0f;
    ratioDisplay->updateRatio(ratio_freq);
    oscillator->modulateFrequency(ratio_freq);
    
    auto [beatSampleIndex, phase, cycleBeatSampleIndex, cyclePhase] = transport->processBlock(bufferToFill);

    beatDisplay->updatePhase(phase);
    barDisplay->updatePhase(transport->calculateBarPhase());

    oscillator->processBlock(buffer,cycleBeatSampleIndex);

    const std::vector<std::vector<float>> sample = {
        body->getChild("hand")->getChild("gyro")->vectorizeState(),
        {cyclePhase},
        {gyro_y,ratio_cycle},
        {gyro_x,ratio_freq},
    };

    graphVector->pushSample(sample);
}