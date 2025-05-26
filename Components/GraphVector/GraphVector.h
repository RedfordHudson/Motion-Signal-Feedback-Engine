#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Grapher;

class GraphVector : public juce::Component
{
public:
    GraphVector(const int size);

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Add a new sample to the buffer
    void pushSample(const std::vector<float> sample);

protected:
    const int size;

private:
    std::vector<std::unique_ptr<Grapher>> graphs;
};