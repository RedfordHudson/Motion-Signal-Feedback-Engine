#include <iostream>
#include <juce_audio_utils/juce_audio_utils.h>

class Cycle;

class Transport {
public:
    Transport(const int BASELINE_BPM, const float ratio);
    ~Transport();

    void prepareToPlay(const float sampleRate);

    const std::tuple<int,float,int,float> processBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    void triggerBeat();

    void updateRatio(const float newRatio);

    const float calculateBarPhase() const;

    const int getBeatCount() const { return beat_count; }

protected:
    const int BASELINE_BPM;

private:
    float SAMPLE_RATE;
    float SAMPLES_PER_BEAT;

    int samples_for_current_beat;
    int beat_count;

    float phase = 0.0f;

    std::unique_ptr<Cycle> cycle;
};