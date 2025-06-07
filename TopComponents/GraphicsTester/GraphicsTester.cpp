#include "GraphicsTester.h"

#include <iostream>

GraphicsTester::GraphicsTester()
{
    setSize(800, 600);

}

void GraphicsTester::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Component Test", getLocalBounds(), juce::Justification::centred, true);
}

void GraphicsTester::resized()
{
    // Called when the component is resized
}
