#include <juce_gui_basics/juce_gui_basics.h>

// utilities / helper functions
inline static void drawCircle(juce::Graphics& g, const juce::Point<float>& center, float radius) {

    // Center the ellipse at center by offsetting top-left corner
    float diameter = radius * 2.0f;

    g.drawEllipse(center.x - radius, center.y - radius, diameter, diameter, 1.0f);
}

inline static void plotPath(juce::Graphics& g, const std::vector<juce::Point<float>>& points, const juce::Colour& color = juce::Colours::white) {
    g.setColour(color);

    if (points.empty())
        return;

    juce::Path path;
    
    // Start at first point
    path.startNewSubPath(points[0]);

    // Draw lines to subsequent points
    for (size_t i = 1; i < points.size(); ++i)
        path.lineTo(points[i]);

    g.strokePath(path, juce::PathStrokeType(2.0f));
}
