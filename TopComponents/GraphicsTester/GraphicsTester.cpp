#include "GraphicsTester.h"

#include <Cycloid.h>

#include <iostream>

GraphicsTester::GraphicsTester()
    :cycloid(std::make_unique<Cycloid>("epi",0.3f))
{
    setSize(800, 600);

    addAndMakeVisible(*cycloid);
    cycloid->setBounds(getLocalBounds()); // make cycloid's size > 0

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
