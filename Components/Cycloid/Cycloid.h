#pragma once

#include "utils.h"

class Cycloid : public juce::Component {
public:
    Cycloid(const std::string& type, const float ratio)
        : type(type), ratio(ratio)
    {}

    void paint(juce::Graphics& g) override {

        // background
        g.fillAll(juce::Colours::black);

        // border
        g.setColour(juce::Colours::grey);
        g.drawRect(getLocalBounds(), 1);

        // main circle
        drawCircle(g,origin,core_radius);
    }

    void resized() override {
        origin = { getWidth() / 2.0f, getHeight() / 2.0f };

        core_radius = (float)getHeight() / (4.0f + 0.15f);

        repaint();
    }

protected:
    const std::string type;

    juce::Point<float> origin;
    float core_radius;
    float ratio;

    void updateRatio(const float newRatio) {
        ratio = newRatio;
    }

    const unsigned int resolution = 500;

private:

    // macro for safe memory management
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Cycloid)
};