#include "TestComponent.h"

TestComponent::TestComponent()
{
    setSize(800, 600);
}

void TestComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("LFG!", getLocalBounds(), juce::Justification::centred, true);
}

void TestComponent::resized()
{
    // Called when the component is resized
}
