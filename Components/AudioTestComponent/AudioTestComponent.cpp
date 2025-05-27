#include "AudioTestComponent.h"

#include <SerialMonitor.h>
#include <HumanWare.h>
#include <Transport.h>
#include <OscillatorWrapper.h>
#include <GraphVector.h>

AudioTestComponent::AudioTestComponent()
    : 
    serialMonitor(std::make_unique<SerialMonitor>("monitor",6)),
    body(std::make_unique<Body>()),
    transport(std::make_unique<Transport>(40)),
    oscillator(std::make_unique<OscillatorWrapper>(300.f))
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels


    const std::vector<GraphMeta> meta = {
        {"accel", "spatial", {"x", "y", "z"}},
        {"gyro", "spatial", {"x", "y", "z"}},
        {"transport", "rhythmic", {"phase", "cyclePhase"}}
    };

    GraphMetaVector graphMetaVector(meta);
    
    graphVector = std::make_unique<GraphVector>(graphMetaVector);

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

    const float x = body->getChild("hand")->getChild("accel")->getValue("x");

    graphVector->pushSample({x,phase,cyclePhase});
}