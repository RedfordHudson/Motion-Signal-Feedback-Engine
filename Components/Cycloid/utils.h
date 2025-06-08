#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

// declaration (necessary to avoid clashing definition caused by multiple includes)
inline void drawCircle(juce::Graphics& g, const juce::Point<float>& center, float radius, const juce::Colour& color = juce::Colours::white);

// definition
inline void drawCircle(juce::Graphics& g, const juce::Point<float>& center, float radius, const juce::Colour& color) {
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

// fades opacity with index
template <typename Container>
inline static void plotFadePath(juce::Graphics& g, const Container& points, const juce::Colour& baseColor = juce::Colours::white) {
    if (points.size() < 2)
        return;

    for (size_t i = 1; i < points.size(); ++i) {
        float alpha = static_cast<float>(i) / (points.size() - 1); // from 0 (oldest) to 1 (newest)
        juce::Colour c = baseColor.withAlpha(alpha);

        juce::Path segmentPath;
        segmentPath.startNewSubPath(points[i - 1]);
        segmentPath.lineTo(points[i]);

        g.setColour(c);
        g.strokePath(segmentPath, juce::PathStrokeType(2.0f));
    }
}
