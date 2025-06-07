#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

// utilities / helper functions
inline static void drawCircle(juce::Graphics& g, const juce::Point<float>& center, float radius) {

    // Center the ellipse at center by offsetting top-left corner
    float diameter = radius * 2.0f;

    g.drawEllipse(center.x - radius, center.y - radius, diameter, diameter, 1.0f);
}

class Cycloid : public juce::Component {
public:
    Cycloid(const std::string& type, const float ratio)
        : type(type), ratio(ratio)
    {
        // setBounds(getLocalBounds());
    }

    void paint(juce::Graphics& g) override {

        origin = { getWidth() / 2.0f, getHeight() / 2.0f };

        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.setFont(20.0f);
        g.drawText("cycloid", getLocalBounds(), juce::Justification::centred, true);

        // main circle
        drawCircle(g,origin,core_radius);

    }

    void resized() override {
        // Layout logic if needed
        repaint();
    }

protected:
    const std::string type;

    const float core_radius = 100.0f;
    float ratio;

    void updateRatio(const float newRatio) {
        ratio = newRatio;
    }

    float resolution = 500;

private:
    juce::Point<float> origin;

    // macro for safe memory management
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Cycloid)
};