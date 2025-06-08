#include "GraphicsTester.h"

#include <FrequencyDisplay.h>
#include <BarDisplay.h>
#include <BeatDisplay.h>

#include <iostream>

GraphicsTester::GraphicsTester()
    :frequencyDisplay(std::make_unique<FrequencyDisplay>()),
    barDisplay(std::make_unique<BarDisplay>()),
    beatDisplay(std::make_unique<BeatDisplay>(1.0f/8.0f))
{

    addAndMakeVisible(*frequencyDisplay);
    addAndMakeVisible(*barDisplay);
    addAndMakeVisible(*beatDisplay);

    setSize(800, 600);

    startTimerHz(30); // updates 30 times per second

}

void GraphicsTester::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Draw border
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);
}

void GraphicsTester::resized() {
    juce::FlexBox flexbox;
    flexbox.flexDirection = juce::FlexBox::Direction::column;

    for (auto* child : getChildren()) {
        flexbox.items.add(juce::FlexItem(*child).withFlex(1.0f));
    }

    flexbox.performLayout(getLocalBounds());
}


void GraphicsTester::timerCallback() {
    // static keyword makes phase retain its value across calls, even though it's declared inside the function
    static float phase = 0.0f;

    phase += 0.01f;
    if (phase >= 1.0f)
        phase -= 1.0f;
    
    if (beatDisplay)
        barDisplay->updatePhase(phase);
        beatDisplay->updatePhase(phase);

}
