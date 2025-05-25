#include <iostream>
#include <juce_audio_utils/juce_audio_utils.h>

class Transport {
public:
    Transport(const int BASELINE_BPM);
    ~Transport() {}

    void prepareToPlay(const double sampleRate);

    void processBlock(const juce::AudioSourceChannelInfo& bufferToFill);

    void triggerBeat();
    
protected:
    const int BASELINE_BPM;
private:
    int samples_for_current_beat;
    int beat_count;

    double SAMPLE_RATE;
    double SAMPLES_PER_BEAT;
};