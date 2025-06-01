#include <iostream>
#include <juce_audio_utils/juce_audio_utils.h>

class Cycle;

class Transport {
public:
    Transport(const int BASELINE_BPM);
    ~Transport();

    void prepareToPlay(const float sampleRate);

    const std::tuple<int,float,int,float> processBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    void triggerBeat();

    void modulateN(const int n);

protected:
    const int BASELINE_BPM;

private:
    float SAMPLE_RATE;
    float SAMPLES_PER_BEAT;

    int samples_for_current_beat;
    int beat_count;

    std::unique_ptr<Cycle> cycle;
};