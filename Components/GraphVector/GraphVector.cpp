#include "GraphVector.h"
#include <iostream>

#include <Grapher.h>

GraphVector::GraphVector(const int size)
    : size(size)
{
    const int width = 600;
    const int height = 600;

    for (int i = 0; i < size; i++) {
        graphs.push_back(std::make_unique<Grapher>(width,height/size));
    }
    
    setSize(width, height);

    for (auto& graph : graphs) {
        addAndMakeVisible(*graph);
    }
}

void GraphVector::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(juce::Colours::black);
    
    // Draw border
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);

}

void GraphVector::resized()
{
    auto area = getLocalBounds();
    int graphHeight = area.getHeight() / size;

    for (int i = 0; i < size; ++i)
    {
        graphs[i]->setBounds(0, i * graphHeight, area.getWidth(), graphHeight);
    }
}

void GraphVector::pushSample(const std::vector<float> sample) {
    jassert(size == sample.size());

    for (int i = 0; i < size; i++)
        graphs[i]->pushSample(sample[i]);
}