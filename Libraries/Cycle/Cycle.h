#include <juce_audio_utils/juce_audio_utils.h>
#include <iostream>

class Cycle {
public:
    Cycle(const float ratio);
    ~Cycle() {}
    
    void prepareToPlay(const float parent_samples_per_beat);

    const int Cycle::processBlock(const int buffer_size);

    const float getPhase() const;

    void synchronizeToTransport(const int transport_samples_for_current_beat);

    void updateRatio(const float newRatio);

protected:
    float ratio;

private:
    std::vector<int> pattern;
    float PARENT_SAMPLES_PER_BEAT;
    float SAMPLES_PER_BEAT;

    int samples_for_current_beat;
};