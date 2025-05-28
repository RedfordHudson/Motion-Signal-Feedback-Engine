#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

#include <tuple>
#include <map>

// wrapper for graph meta data
class GraphMeta {

// remains immutable and encapsulated unless explicitly accessed by the intended consumer
friend class Grapher; 

public:
    GraphMeta(std::string name, std::string type, std::vector<std::string> fields)
        : name(std::move(name)), type(std::move(type)), fields(std::move(fields)) {}
    ~GraphMeta() {}
private:
    std::string name;
    std::string type;
    std::vector<std::string> fields;
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

    // == [ legend ] ==

    std::vector<std::unique_ptr<juce::Label>> legendComponents;
    void generateLegend(const int fieldIndex, const juce::Colour& color);
    void initializeLegend();  // New method to handle legend initialization

    // == [ store ] ==    

    std::vector<std::vector<float>> buffers;

    // == [ color ] ==

    const juce::Colour& getBorderColor() const;
    const std::map<std::string, juce::Colour> borderColorMap = {
        {"sensor", juce::Colours::yellow},
        {"rhythmic", juce::Colours::blue},
        {"parameter", juce::Colours::green}
    };

    const juce::Colour& getPathColor(const int fieldIndex) const;
    const std::map<std::string, juce::Colour> sensorColorMap = {
        {"x", juce::Colours::red},
        {"y", juce::Colours::green},
        {"z", juce::Colours::blue}
    };

    // == [ plot ] ==

    float margin = 20.0f;
    float minValue = 0.0;
    float maxValue = 1.0;

    int cur_length = 0;
    int windowSize = 500;

    float valueToY(float value) const;
    float indexToX(int index) const;
    void renderPlot(juce::Graphics& g, const int fieldIndex);

};