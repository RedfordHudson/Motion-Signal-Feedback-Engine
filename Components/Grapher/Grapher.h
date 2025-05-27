#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <tuple>

struct GraphMeta {
    std::string name;
    std::string type;
    std::vector<std::string> fields;

    GraphMeta(std::string name, std::string type, std::vector<std::string> fields)
        : name(std::move(name)), type(std::move(type)), fields(std::move(fields)) {}
};


class Grapher : public juce::Component
{
public:
    Grapher(
        const GraphMeta& metaData,
        const int width, 
        const int height);

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Add a new sample to the buffer
    void pushSample(const std::vector<float> sample);

protected:
    const std::string name;
    const std::string type;
    const std::vector<std::string> fields;
    const int size;

private:

    // Convert buffer value to y coordinate
    float valueToY(float value) const;
    
    // Convert buffer index to x coordinate
    float indexToX(int index) const;

    juce::Path renderPlot(const int bufferIndex);

    std::vector<std::vector<float>> buffers;
    float margin = 20.0f;  // Margin around the plot
    
    // Track min/max values for scaling
    float minValue = 0.0;
    float maxValue = 1.0;
    int cur_length = 0;

    int windowSize = 500;
};