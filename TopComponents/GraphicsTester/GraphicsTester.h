#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Cycloid;

class GraphicsTester : public juce::Component
{
public:
    GraphicsTester();
    void paint(juce::Graphics& g) override;
    void resized() override;

private:

    std::unique_ptr<Cycloid> cycloid;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphicsTester)
};
