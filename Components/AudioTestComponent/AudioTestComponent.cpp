#include "AudioTestComponent.h"

#include <Transport.h>
#include <Grapher.h>

AudioTestComponent::AudioTestComponent()
    : transport(std::make_unique<Transport>(160)),
    grapher(std::make_unique<Grapher>())
    // oscillator()
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
    // Initialize any audio processing here
    transport->prepareToPlay(sampleRate);
}

void AudioTestComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Clear the buffer
    bufferToFill.clearActiveBufferRegion();

    const float phase = transport->processBlock(bufferToFill);
    grapher->pushSample(phase);
}