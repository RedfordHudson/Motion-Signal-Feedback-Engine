#include "Cycloid.h"

class StaticCycloid : public Cycloid {
public:
    StaticCycloid(const std::string& type, const float ratio)
        : Cycloid(type,ratio)
    {}

    void paint(juce::Graphics& g) override {

        // super().paint()
        Cycloid::paint(g);

        plotPath(g, generateCycloidTrace(), juce::Colours::red);
    }

    void updateRatio(const float newRatio) {
        Cycloid::updateRatio(newRatio);

        // static -> updateRatio() triggers repaint
        // dynamic -> updatePhase() triggers repaint
        repaint();
    }

private:
    std::vector<juce::Point<float>> generateCycloidTrace()
    {
        std::vector<juce::Point<float>> trace;
        trace.reserve(resolution); // performance optimization

        int wraps = 10;

        const float twoPi = juce::MathConstants<float>::twoPi;
        const float r = ratio * core_radius; // sub_radius

        for (unsigned int i = 0; i < resolution; ++i)
        {
            float theta = (static_cast<float>(i) / (resolution - 1)) * wraps * twoPi;

            float x = (core_radius + r) * std::cos(theta) - r * std::cos((core_radius / r + 1) * theta) + origin.x;
            float y = (core_radius + r) * std::sin(theta) - r * std::sin((core_radius / r + 1) * theta) + origin.y;

            trace.emplace_back(x, y);
        }

        return trace;
    }
};