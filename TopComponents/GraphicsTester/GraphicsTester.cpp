#include "GraphicsTester.h"

#include <FrequencyDisplay.h>

#include <iostream>

GraphicsTester::GraphicsTester()
    :frequencyDisplay(std::make_unique<FrequencyDisplay>())
{
    setSize(800, 600);

    addAndMakeVisible(*frequencyDisplay);
    frequencyDisplay->setBounds(getLocalBounds()); // make FrequencyDisplay's size > 0

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
