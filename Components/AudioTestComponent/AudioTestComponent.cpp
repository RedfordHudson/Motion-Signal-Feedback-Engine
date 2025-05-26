#include "AudioTestComponent.h"

#include <Transport.h>
#include <OscillatorWrapper.h>
#include <Grapher.h>

AudioTestComponent::AudioTestComponent()
    : transport(std::make_unique<Transport>(160)),
    oscillator(std::make_unique<OscillatorWrapper>(300.f)),
    grapher(std::make_unique<Grapher>())
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels

    addAndMakeVisible(*grapher);
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
    oscillator->processBlock(buffer);

    const float phase = transport->processBlock(bufferToFill);
    grapher->pushSample(phase);
}