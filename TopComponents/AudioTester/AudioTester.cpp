#include "AudioTester.h"

#include <algorithm>

AudioTester::AudioTester()
{
    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels
}

AudioTester::~AudioTester() {
    shutdownAudio();
}

void AudioTester::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
}

void AudioTester::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Clear the buffer
    bufferToFill.clearActiveBufferRegion();

    juce::AudioBuffer<float>& buffer = *bufferToFill.buffer;
}