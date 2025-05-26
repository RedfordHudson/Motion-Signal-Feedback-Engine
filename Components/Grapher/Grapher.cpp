#include "Grapher.h"
#include <iostream>

Grapher::Grapher()
{
    setSize(300, 300);
    
    // Initialize with some random test data
    
    buffer = {1.0,4.0,3.0};
    
    updateRange();
}

void Grapher::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Draw border
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);

    // delimit critical section
    {
        // juce::ScopedLock lock(bufferLock);
        snapshot = buffer;
    }

    if (snapshot.empty())
    {
        return;
    }

    // updateRange(); 
    
    // Draw the waveform
    g.setColour(juce::Colours::white);
    g.strokePath(renderPlot(), juce::PathStrokeType(2.0f));
}

void Grapher::resized()
{
    // Trigger repaint when size changes
    repaint();
}

void Grapher::updateRange()
{
    if (snapshot.empty())
    {
        minValue = 0.0;
        maxValue = 1.0;
        return;
    }
    
    minValue = snapshot[0];
    maxValue = snapshot[0];
    
    for (const auto& value : snapshot)
    {
        minValue = std::min(minValue, value);
        maxValue = std::max(maxValue, value);
    }
    
    // Add a small margin to the range
    float range = maxValue - minValue;
    if (range == 0.0) range = 1.0;  // Prevent division by zero
    minValue -= range * 0.1;
    maxValue += range * 0.1;
}

float Grapher::valueToY(float value) const
{
    // Convert value to y coordinate, scaled to min/max range
    float height = getHeight() - 2 * margin;
    float normalizedValue = (value - minValue) / (maxValue - minValue);
    return getHeight() - margin - normalizedValue * height;
}

float Grapher::indexToX(int index) const
{
    // Convert snapshot index to x coordinate
    float width = getWidth() - 2 * margin;
    return margin + index * width / (snapshot.size() - 1);
}

juce::Path Grapher::renderPlot()
{
    juce::Path path;
    
    if (snapshot.empty())
        return path;

    // Start at first point
    path.startNewSubPath(indexToX(0), valueToY(snapshot[0]));

    // Draw lines to subsequent points
    for (size_t i = 1; i < snapshot.size(); ++i)
    {
        path.lineTo(indexToX(i), valueToY(snapshot[i]));
    }

    return path;
}

void Grapher::pushSample(const float sample)
{
    // juce::ScopedLock lock(bufferLock);
    buffer.push_back(sample);
    
    // Clamp buffer size to windowSize
    if (buffer.size() > windowSize)
    {
        buffer.erase(buffer.begin(), buffer.begin() + (buffer.size() - windowSize));
    }
    
    repaint();
}