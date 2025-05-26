#include "Cycle.h"

Cycle::Cycle(int n)
    : n(n)
{
    samples_for_current_beat = 0;
    beat_count = 0;
}

void Cycle::prepareToPlay(const float parent_samples_per_beat) {
    SAMPLES_PER_BEAT = parent_samples_per_beat / n;
}

void Cycle::updatePattern(std::vector<int> newPattern) {
    pattern = newPattern;
}

std::tuple<int,float> Cycle::processBlock(const int buffer_size) {
    
    samples_for_current_beat += buffer_size;

    // get index in buffer when next beat should start
    int cycleBeatSampleIndex = static_cast<int>(SAMPLES_PER_BEAT) - samples_for_current_beat;
    
    bool triggerBeat = false;

    if (cycleBeatSampleIndex < buffer_size) {
        // triggerCycleBeat();
        samples_for_current_beat -= static_cast<int>(SAMPLES_PER_BEAT);
        triggerBeat = onPattern();
        beat_count++;

        if (beat_count == n)
            beat_count = 0;
    }

    // prevent beat from being triggered
    if (!triggerBeat)
        cycleBeatSampleIndex = -1;

    // const float cyclePhase = samples_for_current_beat / SAMPLES_PER_BEAT;
    const float cyclePhase = (float)beat_count / n;

    return std::make_tuple(cycleBeatSampleIndex,cyclePhase);
}

const bool Cycle::onPattern() {
    // return (beat_count in pattern)
    return std::find(pattern.begin(), pattern.end(), beat_count) != pattern.end();
}