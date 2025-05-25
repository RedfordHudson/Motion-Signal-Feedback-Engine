#include "TestComponent.h"

// include in implementation file to isolate compilation of Grapher component
// switching to pointers with forward declarations is the best way to decouple headers and speed builds
#include <Grapher.h>
#include <HumanWare.h>
#include <SerialSimulator.h>

#include <iostream>

TestComponent::TestComponent()
    // initialize smart pointer to grapher instance
    : grapher(std::make_unique<Grapher>()),
    body(std::make_unique<Body>()),
    serialSimulator(std::make_unique<SerialSimulator>())
{
    addAndMakeVisible(*grapher);
    setSize(800, 600);

    onBodyUpdated = [this]() {
        double flexValue;
        {
            // scoped lock
            const juce::ScopedLock sl(bodyLock);
            flexValue = body->getChild("flex")->getValue("x");
        }
        grapher->pushSample(flexValue);
    };

    // set callback for serial simulator
    serialSimulator->setCallback([this](const std::vector<double> sample) {
        // scoped lock
        const juce::ScopedLock sl(bodyLock);
        
        body->processSample(sample);
        onBodyUpdated();
    });
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
