#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Grapher : public juce::Component
{
public:
    Grapher(const int width, const int height);

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Add a new sample to the buffer
    void pushSample(const float sample);

private:
    // Convert buffer value to y coordinate
    float valueToY(float value) const;
    
    // Convert buffer index to x coordinate
    float indexToX(int index) const;

    juce::Path renderPlot();

    std::vector<float> buffer;
    float margin = 20.0f;  // Margin around the plot
    
    // Track min/max values for scaling
    float minValue = 0.0;
    float maxValue = 1.0;

    int windowSize = 500;

    // thread safety
    juce::CriticalSection bufferLock;
};