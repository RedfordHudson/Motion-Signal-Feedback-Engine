#include "utils.h"

class Comet {
public:
    Comet(const juce::Point<float> origin, const float core_radius,const float theta) 
        :origin(origin), core_radius(core_radius), theta(theta)
    {}
    ~Comet() = default;

    const bool updateTrail() {
        // Clamp trail size
        if (trail_points.size() > trail_length) {
            // remove oldest point
            trail_points.pop_front();
        }

        ++age;

        // signal death
        if (age == ( life_span + trail_length ))
            return true;

        // stop growing, start diminishing
        if (age >= life_span) {
            if (!trail_points.empty())
                trail_points.pop_front();
            return false;
        }

        // Tracing point (edge of small circle)
        float tx = origin.x + (core_radius + ((float)age) * velocity) * std::cos(theta);
        float ty = origin.y + (core_radius + ((float)age) * velocity) * std::sin(theta);

        // float cx = origin.x + (core_radius - sub_radius) * std::cos(theta);
        // float cy = origin.y + (core_radius - sub_radius) * std::sin(theta);

        trail_points.push_back(juce::Point<float>(tx,ty));

        return false;
    }

    const std::deque<juce::Point<float>> getTrail() const { return trail_points; }

protected:
    const juce::Point<float> origin;
    const float core_radius;
    const float theta;

private:
    std::deque<juce::Point<float>> trail_points; // initializes automatically

    const unsigned int trail_length = 10;
    const unsigned int life_span = 20;
    unsigned int age = 0;
    const float velocity = 2.0f;
};