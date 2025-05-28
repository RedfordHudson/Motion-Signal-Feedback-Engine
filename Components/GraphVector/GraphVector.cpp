#include "GraphVector.h"
#include <iostream>

#include <Grapher.h>

GraphVector::GraphVector(const std::vector<GraphMeta>& meta)
    : size(meta.size())
{
    const int width = 800;
    const int height = 600;

    for (int i = 0; i < size; i++) {
        graphs.push_back(std::make_unique<Grapher>(std::move(GraphMeta(meta[i])), width, height/size));
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

void GraphVector::pushSample(const std::vector<std::vector<float>> sample) {

    if (sample.size() != size) {
        std::cout << "GraphVector: incorrect sample size" << std::endl;
        return;
    }

    for (int i = 0; i < size; i++)
        graphs[i]->pushSample(sample[i]);
}