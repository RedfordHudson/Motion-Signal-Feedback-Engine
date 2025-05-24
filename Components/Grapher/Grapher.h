#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Grapher : public juce::Component
{
public:
    Grapher();

    void paint(juce::Graphics& g) override;
};