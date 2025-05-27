#include "Grapher.h"
#include <iostream>

Grapher::Grapher(const int width, const int height)
{
    setSize(width, height);
}

void Grapher::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Draw border
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);

    if (buffer.empty())
        return;
    
    // Draw the waveform
    g.setColour(juce::Colours::white);
    g.strokePath(renderPlot(), juce::PathStrokeType(2.0f));
}

void Grapher::resized()
{
    // Trigger repaint when size changes
    repaint();
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
    // Convert buffer index to x coordinate
    float width = getWidth() - 2 * margin;
    return margin + index * width / (buffer.size() - 1);
}

juce::Path Grapher::renderPlot()
{
    juce::Path path;
    
    // Start at first point
    path.startNewSubPath(indexToX(0), valueToY(buffer[0]));

    // Draw lines to subsequent points
    for (size_t i = 1; i < buffer.size(); ++i)
    {
        path.lineTo(indexToX(i), valueToY(buffer[i]));
    }

    return path;
}

void Grapher::pushSample(const float sample)
{
    // juce::ScopedLock lock(bufferLock);
    buffer.push_back(sample);

    // update range
    minValue = std::min(minValue, sample);
    maxValue = std::max(maxValue, sample);
    
    // Clamp buffer size to windowSize
    if (buffer.size() > windowSize)
    {
        buffer.erase(buffer.begin(), buffer.begin() + (buffer.size() - windowSize));
    }
    
    repaint();
}