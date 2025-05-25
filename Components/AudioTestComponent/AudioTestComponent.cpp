#include "AudioTestComponent.h"

AudioTestComponent::AudioTestComponent()
    : transport(std::make_unique<Transport>(160))
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels

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

    transport->processBlock(bufferToFill);
}