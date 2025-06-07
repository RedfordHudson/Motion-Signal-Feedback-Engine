#include <juce_gui_basics/juce_gui_basics.h>

// utilities / helper functions
inline static void drawCircle(juce::Graphics& g, const juce::Point<float>& center, float radius, const juce::Colour& color = juce::Colours::white) {
    g.setColour(color);

    // Center the ellipse at center by offsetting top-left corner
    float diameter = radius * 2.0f;

    g.drawEllipse(center.x - radius, center.y - radius, diameter, diameter, 1.0f);
}

// can accept either vectors or deques, as long as they contain juce::Points
template <typename Container>
inline static void plotPath(juce::Graphics& g, const Container& points, const juce::Colour& color = juce::Colours::white) {
    g.setColour(color);

    if (points.empty())
        return;

    auto it = std::begin(points);
    juce::Path path;
    path.startNewSubPath(*it);

    for (++it; it != std::end(points); ++it)
        path.lineTo(*it);

    g.strokePath(path, juce::PathStrokeType(2.0f));
}
