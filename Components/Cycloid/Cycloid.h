#pragma once

#include "utils.h"

class Cycloid : public juce::Component {
public:
    Cycloid(const std::string& name, const std::string& type, const float ratio)
        : name(name), type(type), ratio(ratio)
    {
        generateNameLabel();
    }

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

        // Calculate width based on text size
        int width = juce::Font(14.0f).getStringWidth(name) + 20;

        nameLabel->setBounds( (getWidth() - width)/2, getHeight() - 20, width, 20);

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
    
    const std::string name;
    std::unique_ptr<juce::Label> nameLabel;
    void generateNameLabel() {
        nameLabel = std::make_unique<juce::Label>();
        nameLabel->setText(name, juce::dontSendNotification);
        nameLabel->setColour(juce::Label::textColourId, juce::Colours::white);
        nameLabel->setColour(juce::Label::backgroundColourId, juce::Colours::black);

        nameLabel->setColour(juce::Label::outlineColourId, juce::Colours::white);
        nameLabel->setJustificationType(juce::Justification::centred);

        // Calculate width based on text size
        int width = juce::Font(14.0f).getStringWidth(name);
        // Add padding for the border and some extra space
        width += 20;

        // Position the label dynamically (stacking them below each other, e.g.)
        nameLabel->setBounds( (getWidth() - width)/2, getHeight() - 20, width, 20);

        // std::cout << std::to_string(nameLabel->getBounds().getX()) << ", " << std::to_string(nameLabel->getBounds().getY()) << std::endl;

        addAndMakeVisible(*nameLabel);
    }

    // macro for safe memory management
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Cycloid)
};