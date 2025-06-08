#include "AudioTester.h"

#include <FrequencyDisplay.h>
#include <BarDisplay.h>
#include <BeatDisplay.h>

#include <Transport.h>
#include <OscillatorWrapper.h>

AudioTester::AudioTester()
    :
    transport(std::make_unique<Transport>(40)),
    frequencyDisplay(std::make_unique<FrequencyDisplay>()),
    barDisplay(std::make_unique<BarDisplay>(false)),
    beatDisplay(std::make_unique<BeatDisplay>(4.0f/8.0f,true)),
    oscillator(std::make_unique<OscillatorWrapper>(440.f))
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
    oscillator->prepareToPlay(samplesPerBlockExpected,sampleRate);

    transport->prepareToPlay((float)sampleRate);
}

void AudioTester::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Clear the buffer
    bufferToFill.clearActiveBufferRegion();

    juce::AudioBuffer<float>& buffer = *bufferToFill.buffer;
    
    auto [beatSampleIndex, phase, cycleBeatSampleIndex, cyclePhase] = transport->processBlock(bufferToFill);

    beatDisplay->updatePhase(phase);

    oscillator->processBlock(buffer,beatSampleIndex);
}