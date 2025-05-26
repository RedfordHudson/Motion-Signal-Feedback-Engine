#include "AudioTestComponent.h"

#include <Transport.h>
#include <OscillatorWrapper.h>
#include <GraphVector.h>

AudioTestComponent::AudioTestComponent()
    : transport(std::make_unique<Transport>(160)),
    oscillator(std::make_unique<OscillatorWrapper>(300.f)),
    graphVector(std::make_unique<GraphVector>(2))
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels

    addAndMakeVisible(*graphVector);
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

    oscillator->processBlock(buffer,beatSampleIndex);

    graphVector->pushSample({phase,cyclePhase});
}