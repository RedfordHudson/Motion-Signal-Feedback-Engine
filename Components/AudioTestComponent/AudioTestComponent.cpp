#include "AudioTestComponent.h"

#include <SerialMonitor.h>
#include <HumanWare.h>
#include <Transport.h>
#include <OscillatorWrapper.h>
#include <GraphVector.h>
#include <algorithm>

AudioTestComponent::AudioTestComponent()
    : 
    serialMonitor(std::make_unique<SerialMonitor>("simulate",6)),
    body(std::make_unique<Body>()),
    transport(std::make_unique<Transport>(40)),
    oscillator(std::make_unique<OscillatorWrapper>(300.f)),
    meta({
        GraphMeta("accel", "sensor", {"x", "y", "z"}),
        GraphMeta("gyro", "sensor", {"x", "y", "z"}),
        GraphMeta("transport", "rhythmic", {"phase", "cyclePhase"}),
        GraphMeta("parameter", "parameter", {"gyro_y","n"})
    }),
    graphVector(std::make_unique<GraphVector>(meta))
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels

    addAndMakeVisible(*graphVector);

    serialMonitor->setCallback([this](const std::vector<float> sample) {
        juce::MessageManager::callAsync([this, sample] {
            body->processSample(sample);
        });
    });

    serialMonitor->start();
}

AudioTestComponent::~AudioTestComponent() {
    shutdownAudio();
}

void AudioTestComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    oscillator->prepareToPlay(samplesPerBlockExpected,sampleRate);

    transport->prepareToPlay((float)sampleRate);
}

void AudioTestComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Clear the buffer
    bufferToFill.clearActiveBufferRegion();

    juce::AudioBuffer<float>& buffer = *bufferToFill.buffer;

    auto [beatSampleIndex, phase, cycleBeatSampleIndex, cyclePhase] = transport->processBlock(bufferToFill);

    oscillator->processBlock(buffer,cycleBeatSampleIndex);

    const float gyro_y = body->getChild("hand")->getChild("gyro")->getValue("y") / 17000 * 10;
    int n = static_cast<int>(gyro_y);
    if (n < 0) n = 0;
    ++n;
    transport->modulateN(n);

    const std::vector<std::vector<float>> sample = {
        body->getChild("hand")->getChild("accel")->vectorizeState(),
        body->getChild("hand")->getChild("gyro")->vectorizeState(),
        {phase,cyclePhase},
        {gyro_y,static_cast<float>(n)}
    };

    graphVector->pushSample(sample);
}