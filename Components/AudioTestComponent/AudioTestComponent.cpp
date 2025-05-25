#include "AudioTestComponent.h"

AudioTestComponent::AudioTestComponent()
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels
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