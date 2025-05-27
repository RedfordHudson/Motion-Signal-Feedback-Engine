#include "Grapher.h"
#include <iostream>

Grapher::Grapher(
        const GraphMeta& metaData,
        const int width, 
        const int height)
    :
    name(metaData.name),
    type(metaData.type),
    fields(metaData.fields),
    size(fields.size())
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

    if (cur_length == 0)
        return;

    for (int i = 0; i < size; i++) {
        // Draw the waveform
        g.setColour(juce::Colours::white);
        g.strokePath(renderPlot(i), juce::PathStrokeType(2.0f));
    }
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
    return margin + index * width / (windowSize - 1);
}

juce::Path Grapher::renderPlot(const int bufferIndex)
{
    juce::Path path;

    int start_index = windowSize - cur_length;
    
    // Start at first point
    path.startNewSubPath(indexToX(start_index), valueToY(buffers[bufferIndex][0]));

    // Draw lines to subsequent points
    for (size_t i = start_index + 1; i < cur_length; ++i)
    {
        path.lineTo(indexToX(i), valueToY(buffers[bufferIndex][i]));
    }

    return path;
}

void Grapher::pushSample(const std::vector<float> sample)
{
    if (sample.size() != size) {
        std::cout << "Grapher: incorrect sample size" << std::endl;
        return;
    }

    if (cur_length < windowSize)
        cur_length++;

    for (int i = 0; i < size; i++) {
        buffers[i].push_back(sample[i]);

        // update range
        minValue = std::min(minValue, sample[i]);
        maxValue = std::max(maxValue, sample[i]);

        // Clamp buffer size to windowSize
        if (cur_length == windowSize)
        {
            buffers[i].erase(buffers[i].begin(), buffers[i].begin() + 1);
        }
    }
    
    repaint();
}