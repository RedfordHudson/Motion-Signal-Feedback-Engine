#include "Grapher.h"
#include <iostream>

// GraphMeta&& meta = rvalue -> prepare to be moved
// lvalue = ( std::move(lvalue) -> rvalue )
// std::move converts lvalue to rvalue, enabling transference of ownership
//  -> transfers ownership from rvalue (right hand) to lvalue (left hand)

Grapher::Grapher(
        GraphMeta&& meta, 
        const int width, 
        const int height)
    :
    name(std::move(meta.name)), 
    type(std::move(meta.type)),
    fields(std::move(meta.fields)),
    size(fields.size()),
    buffers(size)  // initialize with size empty vectors
{
    setSize(width, height);
}

void Grapher::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Draw border
    g.setColour(getBorderColor());
    g.drawRect(getLocalBounds(), 1);

    if (cur_length == 0)
        return;

    for (int i = 0; i < size; i++) {
        // Draw the waveform
        const juce::Colour& color = getPathColor(i);
        g.setColour(color);
        renderPlot(g,i);
        // generateLegend(i,color);
    }
}

void Grapher::resized()
{
    // Trigger repaint when size changes
    repaint();
}

// == [ store ] ==    

void Grapher::pushSample(const std::vector<float> sample) {
    if (sample.size() != size) {
        std::cout << "Grapher: incorrect sample size" << std::endl;
        return;
    }

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

    if (cur_length < windowSize)
        cur_length++;
    
    repaint();
}

// == [ color ] ==

const juce::Colour& getColor(const std::map<std::string, juce::Colour>& colorMap, const std::string& key) {
    
    auto it = colorMap.find(key);  // or type.toUTF8() if juce::String
    if (it != colorMap.end())
        return it->second;
    return juce::Colours::grey;

}

const juce::Colour& Grapher::getBorderColor() const {
    return getColor(borderColorMap,type);
}

const juce::Colour& Grapher::getPathColor(const int fieldIndex) const {

    const std::string& field = fields[fieldIndex];
    
    if (type == "sensor")
        return getColor(sensorColorMap,field);
    
    return juce::Colours::white;
}

// == [ plot ] ==

float Grapher::valueToY(float value) const
{
    // Convert value to y coordinate, scaled to min/max range
    float height = getHeight() - 2 * margin;
    float normalizedValue = (value - minValue) / (maxValue - minValue);
    return getHeight() - margin - normalizedValue * height;
}

float Grapher::indexToX(int index) const
{
    return index * getWidth() / (windowSize - 1);
}

void Grapher::renderPlot(juce::Graphics& g, const int fieldIndex)
{
    juce::Path path;
    
    int start_index = 0;
    if (windowSize > cur_length)
        start_index = windowSize - cur_length;
    
    // Start at first point
    path.startNewSubPath(indexToX(start_index), valueToY(buffers[fieldIndex][0]));

    // Draw lines to subsequent points
    for (size_t i = 1; i < cur_length; ++i)
    {
        path.lineTo(indexToX(start_index + i), valueToY(buffers[fieldIndex][i]));
    }

    g.strokePath(path, juce::PathStrokeType(2.0f));
}

// == [ label ] ==

void Grapher::generateLegend(const int fieldIndex, const juce::Colour& color) {
    const std::string& field = fields[fieldIndex];

    auto legendLabel = std::make_unique<juce::Label>();
    legendLabel->setText(field, juce::dontSendNotification);
    legendLabel->setColour(juce::Label::textColourId, color);
    legendLabel->setFont(juce::Font(14.0f));
    legendLabel->setJustificationType(juce::Justification::centredLeft);

    // Position the label dynamically (stacking them below each other, e.g.)
    legendLabel->setBounds(10, 20 + fieldIndex * 20, 150, 20);

    addAndMakeVisible(*legendLabel);
    legendComponents.push_back(std::move(legendLabel)); // Store for lifecycle
}