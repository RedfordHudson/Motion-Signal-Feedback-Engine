#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class FrequencyDisplay;
class BarDisplay;

class GraphicsTester : public juce::Component, private juce::Timer
{
public:
    GraphicsTester();
    void paint(juce::Graphics& g) override;
    void resized() override;

    void timerCallback();

private:

    std::unique_ptr<FrequencyDisplay> frequencyDisplay;
    std::unique_ptr<BarDisplay> barDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphicsTester)
};
