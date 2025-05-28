#include "AudioTestComponent.h"

#include <SerialMonitor.h>
#include <HumanWare.h>
#include <Transport.h>
#include <OscillatorWrapper.h>
#include <GraphVector.h>

AudioTestComponent::AudioTestComponent()
    : 
    serialMonitor(std::make_unique<SerialMonitor>("simulate",6)),
    body(std::make_unique<Body>()),
    transport(std::make_unique<Transport>(40)),
    oscillator(std::make_unique<OscillatorWrapper>(300.f))
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels

    {
        // temporary lifetime -> should "own" data (don't make reference&)
        const std::vector<GraphMeta> meta = {
            GraphMeta("accel", "sensor", {"x", "y", "z"}),
            GraphMeta("gyro", "sensor", {"x", "y", "z"}),
            GraphMeta("transport", "rhythmic", {"phase", "cyclePhase"})
        };

        graphVector = std::make_unique<GraphVector>(meta);
    }

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

    transport->prepareToPlay(sampleRate);
}

void AudioTestComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Clear the buffer
    bufferToFill.clearActiveBufferRegion();

    juce::AudioBuffer<float>& buffer = *bufferToFill.buffer;

    auto [beatSampleIndex, phase, cycleBeatSampleIndex, cyclePhase] = transport->processBlock(bufferToFill);

    oscillator->processBlock(buffer,cycleBeatSampleIndex);

    const std::vector<std::vector<float>> sample = {
        body->getChild("hand")->getChild("accel")->vectorizeState(),
        body->getChild("hand")->getChild("gyro")->vectorizeState(),
        // {1.0,2.0,3.0},
        // {1.0,2.0,3.0},
        {phase,cyclePhase}
    };

    graphVector->pushSample(sample);
}