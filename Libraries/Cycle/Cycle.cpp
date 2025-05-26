#include "Cycle.h"

Cycle::Cycle(int n)
    : n(n)
{

}

void Cycle::prepareToPlay(const float sampleRate, const float parent_samples_per_beat) {

}

void Cycle::updatePattern(std::vector<int> newPattern) {
    pattern = newPattern;
}

const std::tuple<int,float> Cycle::processBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    int cycleBeatSampleIndex = -1;
    float cyclePhase = 0.0;
    return std::make_tuple(cycleBeatSampleIndex,cyclePhase);
}