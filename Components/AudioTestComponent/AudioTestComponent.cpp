#include "AudioTestComponent.h"

#include <SerialSimulator.h>
#include <HumanWare.h>
#include <Transport.h>
#include <OscillatorWrapper.h>
#include <GraphVector.h>

AudioTestComponent::AudioTestComponent()
    : 
    serialSimulator(std::make_unique<SerialSimulator>()),
    body(std::make_unique<Body>()),
    transport(std::make_unique<Transport>(40)),
    oscillator(std::make_unique<OscillatorWrapper>(300.f)),
    graphVector(std::make_unique<GraphVector>(3))
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels

    addAndMakeVisible(*graphVector);

    flexValue = 0;
    
    onBodyUpdated = [this]() {
        double proxyFlexValue;
        {
            // scoped lock
            const juce::ScopedLock sl(bodyLock);
            proxyFlexValue = body->getChild("flex")->getValue("x");
        }
        flexValue = proxyFlexValue;
        // grapher->pushSample(flexValue);
    };

    // set callback for serial simulator
    serialSimulator->setCallback([this](const std::vector<float> sample) {
        // scoped lock
        const juce::ScopedLock sl(bodyLock);
        
        body->processSample(sample);
        onBodyUpdated();
    });

    serialSimulator->startThread();
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


    graphVector->pushSample({flexValue,phase,cyclePhase});
}