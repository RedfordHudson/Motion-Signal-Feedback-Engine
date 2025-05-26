#pragma once

// forward declaration
class Body;
class SerialMonitor;

#include <juce_gui_basics/juce_gui_basics.h>

class TestComponent : public juce::Component
{
public:
    TestComponent();
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    // pointer instead of instance, b/c header is only in implementation (.cpp) file
    // Grapher* grapher;
    // use smart pointer to automatically manage memory and lifecycle
    std::unique_ptr<Body> body;
    std::unique_ptr<SerialMonitor> serialMonitor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestComponent)
};
