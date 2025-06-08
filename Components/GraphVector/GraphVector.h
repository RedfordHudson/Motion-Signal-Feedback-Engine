#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Grapher;
class GraphMeta;

class GraphVector : public juce::Component
{
public:
    GraphVector::GraphVector(const std::vector<GraphMeta>& meta);

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Add a new sample to the buffer
    void pushSample(const std::vector<std::vector<float>> sample);

protected:
    const unsigned int size;

private:
    std::vector<std::unique_ptr<Grapher>> graphs;
};