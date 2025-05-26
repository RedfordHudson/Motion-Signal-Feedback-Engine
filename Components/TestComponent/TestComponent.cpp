#include "TestComponent.h"

// include in implementation file to isolate compilation of Grapher component
// switching to pointers with forward declarations is the best way to decouple headers and speed builds
#include <HumanWare.h>
#include <SerialMonitor.h>

#include <iostream>

TestComponent::TestComponent()
    // initialize smart pointer to grapher instance
    : body(std::make_unique<Body>()),
    serialMonitor(std::make_unique<SerialMonitor>("monitor",6))
{
    setSize(800, 600);

    serialMonitor->setCallback([this](const std::vector<float> sample) {
        juce::MessageManager::callAsync([this, sample] {
            body->processSample(sample);

            const juce::NamedValueSet& gyro = body->getChild("hand")->getChild("gyro")->getState();

            std::cout << "x: " << std::to_string(static_cast<float>(gyro["x"]))
                << "y: " << std::to_string(static_cast<float>(gyro["y"]))
                << "z: " << std::to_string(static_cast<float>(gyro["z"]))
                << std::endl;
        });
    });

    serialMonitor->start();

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
