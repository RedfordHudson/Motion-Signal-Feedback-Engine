#include "AudioTestComponent.h"

AudioTestComponent::AudioTestComponent()
    : transport(std::make_unique<Transport>())
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels

    transport->printStuff();
}

AudioTestComponent::~AudioTestComponent() {
    shutdownAudio();
}

void AudioTestComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    // Initialize any audio processing here
}

void AudioTestComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Clear the buffer
    bufferToFill.clearActiveBufferRegion();
}