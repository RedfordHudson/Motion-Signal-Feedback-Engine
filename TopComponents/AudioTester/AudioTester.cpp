#include "AudioTester.h"

#include <FrequencyDisplay.h>
#include <BarDisplay.h>
#include <BeatDisplay.h>

AudioTester::AudioTester()
    :frequencyDisplay(std::make_unique<FrequencyDisplay>()),
    barDisplay(std::make_unique<BarDisplay>()),
    beatDisplay(std::make_unique<BeatDisplay>(1.0f/8.0f))
{
    addAndMakeVisible(*frequencyDisplay);
    addAndMakeVisible(*barDisplay);
    addAndMakeVisible(*beatDisplay);

    setSize(800, 600);
    setAudioChannels(0, 2); // 0 input channels, 2 output channels
}

AudioTester::~AudioTester() {
    shutdownAudio();
}


void AudioTester::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Draw border
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
}

void AudioTester::resized() {
    juce::FlexBox flexbox;
    flexbox.flexDirection = juce::FlexBox::Direction::column;

    for (auto* child : getChildren()) {
        flexbox.items.add(juce::FlexItem(*child).withFlex(1.0f));
    }

    flexbox.performLayout(getLocalBounds());
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