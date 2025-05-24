#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Grapher : public juce::Component
{
public:
    Grapher();

    void paint(juce::Graphics& g) override;

    juce::Path renderBuffer();
private:
    std::vector<double> buffer = {1.0,3.0,2.0};
};