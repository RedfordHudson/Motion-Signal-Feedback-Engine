#include "Cycle.h"

Cycle::Cycle(const float ratio)
    :ratio(ratio)
{
    samples_for_current_beat = 0;
}

void Cycle::prepareToPlay(const float parent_samples_per_beat) {
    this->PARENT_SAMPLES_PER_BEAT = parent_samples_per_beat;
    SAMPLES_PER_BEAT = parent_samples_per_beat * ratio;
}

const int Cycle::processBlock(const int buffer_size) {
    
    samples_for_current_beat += buffer_size;

    // get index in buffer when next beat should start
    const int cycleBeatSampleIndex = static_cast<int>(SAMPLES_PER_BEAT) - samples_for_current_beat;
    
    // beat is primed
    if (cycleBeatSampleIndex < buffer_size) {
        samples_for_current_beat -= static_cast<int>(SAMPLES_PER_BEAT);
    }

    return cycleBeatSampleIndex;
}

const float Cycle::getPhase() const { return (float)samples_for_current_beat / SAMPLES_PER_BEAT; }

void Cycle::synchronizeToTransport(const int transport_samples_for_current_beat) {
    samples_for_current_beat = transport_samples_for_current_beat;
}

void Cycle::updateRatio(const float newRatio) {
    ratio = newRatio;
    SAMPLES_PER_BEAT = PARENT_SAMPLES_PER_BEAT * ratio;
}