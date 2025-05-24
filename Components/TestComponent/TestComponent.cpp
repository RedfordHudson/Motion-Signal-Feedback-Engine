#include "TestComponent.h"

// include in implementation file to isolate compilation of Grapher component
// switching to pointers with forward declarations is the best way to decouple headers and speed builds
#include <Grapher.h>

TestComponent::TestComponent()
    // initialize smart pointer to grapher instance
    : grapher(std::make_unique<Grapher>())
{
    addAndMakeVisible(*grapher);

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
