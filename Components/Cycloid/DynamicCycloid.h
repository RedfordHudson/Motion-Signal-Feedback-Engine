#include "Cycloid.h"

class DynamicCycloid : public Cycloid {
public:
    DynamicCycloid(const std::string& type, const float ratio)
        : Cycloid(type,ratio),
        sub_radius(core_radius * ratio)
    {
    }

    void paint(juce::Graphics& g) override {

        // super().paint()
        Cycloid::paint(g);

        // roller circle
        drawCircle(g,sub_center,sub_radius);

        // tracer
        plotFadePath(g,tracer_points,juce::Colours::green);

        // tracer node
        if (tracer_points.empty())
            return;
        
        const juce::Point<float> tracer_node_coord = tracer_points.back();
        const float diameter = 10.0f;
        g.fillEllipse(tracer_node_coord.x - diameter/2.0f,tracer_node_coord.y - diameter/2.0f,diameter,diameter);
    }

    void resized() override {
        Cycloid::resized();
        
        updateSubCenter();
    }

    void updatePhase(const float newPhase) {
        phase = newPhase;

        if (phase > 1.0f)
            std::cout << "[WARNING] DynamicCyloid.updatePhase(): phase > 1" << std::endl;

        theta = phase * 2.0f * juce::MathConstants<float>::pi;
        
        updateSubCenter();
        updateTracer();

        repaint();
    }

    void updateRatio(const float newRatio) {
        Cycloid::updateRatio(newRatio);
        sub_radius = core_radius * newRatio;
    }

private:

    void updateSubCenter() {
        float cx = origin.x + (core_radius - sub_radius) * std::cos(theta);
        float cy = origin.y + (core_radius - sub_radius) * std::sin(theta);

        sub_center = { cx,cy };
    }

    void updateTracer() {
        // Tracing point (edge of small circle)
        float phi = (core_radius - sub_radius) / sub_radius * theta;
        float tx = sub_center.x + sub_radius * std::cos(-phi);
        float ty = sub_center.y + sub_radius * std::sin(-phi);

        // Clamp tracer size
        if (tracer_points.size() > tracer_length) {
            // remove oldest point
            tracer_points.pop_front();
        }

        tracer_points.push_back(juce::Point<float>(tx,ty));
    }

    float phase = 0.0f;
    float theta = 0.0f;

    float sub_radius;
    juce::Point<float> sub_center;
    
    std::deque<juce::Point<float>> tracer_points; // initializes automatically
    const float tracer_length = 50;
};
