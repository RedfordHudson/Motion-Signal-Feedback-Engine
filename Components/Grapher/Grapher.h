#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class Grapher : public juce::Component
{
public:
    Grapher();

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Add a new sample to the buffer
    void pushSample(double sample);

private:
    // Convert buffer value to y coordinate
    float valueToY(float value) const;
    
    // Convert buffer index to x coordinate
    float indexToX(int index) const;

    // Update min/max values from buffer
    void updateRange();

    juce::Path renderPlot();

    std::vector<double> buffer;
    std::vector<double> snapshot;;
    float margin = 20.0f;  // Margin around the plot
    
    // Track min/max values for scaling
    double minValue = 0.0;
    double maxValue = 1.0;

    int windowSize = 1000;

    // thread safety
    juce::CriticalSection bufferLock;
};