#pragma once

#include "Cycloid.h"
#include "Comet.h"

class DynamicCycloid : public Cycloid {
public:
    DynamicCycloid(const std::string& name, const std::string& type, const float ratio, const bool master = true)
        : Cycloid(name,type,ratio), master(master)
    {}

    void paint(juce::Graphics& g) override {
        try {
            // super().paint()
            Cycloid::paint(g);

            // roller circle
            drawCircle(g,sub_center,sub_radius);

            renderTracer(g);

            renderComets(g);
        } catch (...) {
            std::cout << "Exception caught in paint()" << std::endl;
        }
    }

    void resized() override {
        Cycloid::resized();
        
        updateSubCenter();
    }

    void updatePhase(const float newPhase) {
        phase = newPhase;
        sub_phase_cur = std::fmod(phase / ratio, 1.0f); // % 

        if (master && sub_phase_cur < sub_phase_prev) {
            beatEvent();
        }

        sub_phase_prev = sub_phase_cur;

        if (phase > 1.0f)
            std::cout << "[WARNING] DynamicCyloid.updatePhase(): phase > 1" << std::endl;

        theta = phase * 2.0f * juce::MathConstants<float>::pi;
        
        updateSubCenter();
        updateTracer();

        updateComets();
     
        repaint();
    }

    void updateRatio(const float newRatio) {
        Cycloid::updateRatio(newRatio);
        sub_radius = core_radius * newRatio;
    }

    void beatEvent() {
        // std::cout << std::to_string(sub_phase_cur) << "-" << std::to_string(sub_phase_prev) << std::endl;
        comets.push_back(std::make_unique<Comet>(origin,core_radius,theta));
    }

protected:
    // true -> triggers comets internally
    // false -> consumes triggers externally
    const bool master;

private:

    void updateSubCenter() {
        
        sub_radius = core_radius * ratio;

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
            if (tracer_points.empty())
                std::cout << "updateTracer(): cooked" << std::endl;
            // remove oldest point
            tracer_points.pop_front();
        }

        tracer_points.push_back(juce::Point<float>(tx,ty));
    }

    void renderTracer(juce::Graphics& g) {
        if (tracer_points.empty())
            return;

        // Get a copy for safe iteration and access outside the lock
        auto pointsCopy = tracer_points.getCopy();

        if (pointsCopy.empty())
            return;

        // Draw tracer path from the copy
        plotFadePath(g, pointsCopy, juce::Colours::green);

        // Draw tracer node using last point in copy
        const juce::Point<float>& tracer_node_coord = pointsCopy.back();
        const float diameter = 10.0f;
        g.fillEllipse(tracer_node_coord.x - diameter / 2.0f,
                    tracer_node_coord.y - diameter / 2.0f,
                    diameter, diameter);
    }

    void updateComets() {
        bool destroyFirst = false;

        for (auto& comet : comets) {
            if (comet->updateTrail())
                destroyFirst = true;
        }

        if (destroyFirst) {
            comets.pop_front();
        }
    }

    void renderComets(juce::Graphics& g) {
        for (auto& comet : comets) {
            plotFadePath(g,comet->getTrail(),juce::Colours::green);
        }
    }


    float phase = 0.0f;
    float sub_phase_cur = 0.0f;
    float sub_phase_prev = 0.0f;
    float theta = 0.0f;

    float sub_radius = 1.0f;
    juce::Point<float> sub_center;
    
    ThreadSafeDeque<juce::Point<float>> tracer_points; // initializes automatically
    const unsigned int tracer_length = 50;

    std::deque<std::unique_ptr<Comet>> comets;
};
