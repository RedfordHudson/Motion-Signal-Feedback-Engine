#include "GraphicsTester.h"

#include <FrequencyDisplay.h>
#include <BarDisplay.h>

#include <iostream>

GraphicsTester::GraphicsTester()
    :frequencyDisplay(std::make_unique<FrequencyDisplay>()),
    barDisplay(std::make_unique<BarDisplay>())
{
    setSize(800, 600);

    addAndMakeVisible(*barDisplay);
    barDisplay->setBounds(getLocalBounds()); // make display's size > 0

    for (auto i = 0;i<5;i++)
        barDisplay->updatePhase((float)i/50.0f);

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

void GraphicsTester::resized()
{
    // Called when the component is resized
}

void GraphicsTester::timerCallback() {
    // static keyword makes phase retain its value across calls, even though it's declared inside the function
    static float phase = 0.0f;

    phase += 0.01f;
    if (phase >= 1.0f)
        phase -= 1.0f;
    
    if (barDisplay)
        barDisplay->updatePhase(phase);

}
