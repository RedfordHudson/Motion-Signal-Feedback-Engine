#include "AudioTestComponent.h"

AudioTestComponent::AudioTestComponent()
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels
}

AudioTestComponent::~AudioTestComponent()
{
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

void AudioTestComponent::releaseResources()
{
    // Free any resources that were allocated in prepareToPlay
}

void AudioTestComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Audio Test", getLocalBounds(), juce::Justification::centred, true);
}

void AudioTestComponent::resized()
{
    // Called when the component is resized
}
