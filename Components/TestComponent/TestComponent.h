#pragma once

// forward declaration
class Grapher;
class SerialSimulator;

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
    std::unique_ptr<Grapher> grapher;

    std::unique_ptr<SerialSimulator> serialSimulator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TestComponent)
};
