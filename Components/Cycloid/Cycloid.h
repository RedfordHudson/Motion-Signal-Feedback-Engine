#pragma once

#include "utils.h"

class Cycloid : public juce::Component {
public:
    Cycloid(const std::string& type, const float ratio)
        : type(type), ratio(ratio)
    {
        // setBounds(getLocalBounds());
    }

    void paint(juce::Graphics& g) override {
        g.fillAll(juce::Colours::black);

        // main circle
        drawCircle(g,origin,core_radius);
    }

    void resized() override {
        origin = { getWidth() / 2.0f, getHeight() / 2.0f };

        repaint();
    }

protected:
    const std::string type;

    const float core_radius = 100.0f;
    float ratio;
    juce::Point<float> origin;

    void updateRatio(const float newRatio) {
        ratio = newRatio;
    }

    const unsigned int resolution = 500;

private:

    // macro for safe memory management
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Cycloid)
};