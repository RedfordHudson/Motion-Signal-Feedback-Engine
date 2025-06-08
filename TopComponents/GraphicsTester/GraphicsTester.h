#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class FrequencyDisplay;
class BarDisplay;
class BeatDisplay;

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
    std::unique_ptr<BeatDisplay> beatDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphicsTester)
};
