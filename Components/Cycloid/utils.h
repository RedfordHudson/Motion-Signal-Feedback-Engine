#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <deque>

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

template<typename T>
class ThreadSafeDeque {
public:
    void push_back(const T& item) {
        const juce::ScopedLock lock(mutex_);
        deque_.push_back(item);
    }

    void push_front(const T& item) {
        const juce::ScopedLock lock(mutex_);
        deque_.push_front(item);
    }

    bool pop_front() {
        const juce::ScopedLock lock(mutex_);
        if (deque_.empty())
            return false;
        deque_.pop_front();
        return true;
    }

    bool empty() const {
        const juce::ScopedLock lock(mutex_);
        return deque_.empty();
    }

    size_t size() const {
        const juce::ScopedLock lock(mutex_);
        return deque_.size();
    }

    // Access the front/back elements safely - returns a copy
    bool front(T& out) const {
        const juce::ScopedLock lock(mutex_);
        if (deque_.empty())
            return false;
        out = deque_.front();
        return true;
    }

    bool back(T& out) const {
        const juce::ScopedLock lock(mutex_);
        if (deque_.empty())
            return false;
        out = deque_.back();
        return true;
    }

    // Get a copy of the entire deque for safe iteration
    std::deque<T> getCopy() const {
        const juce::ScopedLock lock(mutex_);
        return deque_;
    }

private:
    mutable juce::CriticalSection mutex_;
    std::deque<T> deque_;
};
