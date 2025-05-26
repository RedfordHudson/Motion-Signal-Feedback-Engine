#include <juce_audio_utils/juce_audio_utils.h>
#include <iostream>

class Cycle {
public:
    Cycle(int n);
    ~Cycle() {}
    
    void prepareToPlay(const float parent_samples_per_beat);

    void updatePattern(std::vector<int> newPattern);
    
    std::tuple<int,float> Cycle::processBlock(const int buffer_size);

    const bool onPattern();

protected:
    int n;

private:
    std::vector<int> pattern;
    float SAMPLES_PER_BEAT;

    int samples_for_current_beat;
    int beat_count;
};