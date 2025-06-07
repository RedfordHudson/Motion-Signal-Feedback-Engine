#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class FrequencyDisplay;

class GraphicsTester : public juce::Component
{
public:
    GraphicsTester();
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    std::unique_ptr<FrequencyDisplay> frequencyDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphicsTester)
};
