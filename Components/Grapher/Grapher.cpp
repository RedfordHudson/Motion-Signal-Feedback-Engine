#include "Grapher.h"

Grapher::Grapher()
{
    setSize(300, 300);
}

void Grapher::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::blue);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("plot", getLocalBounds(), juce::Justification::centred, true);
}
