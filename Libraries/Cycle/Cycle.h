#include <juce_audio_utils/juce_audio_utils.h>
#include <iostream>

class Cycle {
public:
    Cycle(int n);
    ~Cycle() {}
    
    void prepareToPlay(const float sampleRate, const float parent_samples_per_beat);

    void updatePattern(std::vector<int> newPattern);
    
    const std::tuple<int,float> Cycle::processBlock(const juce::AudioSourceChannelInfo& bufferToFill);

protected:
    int n;
private:
    std::vector<int> pattern;
};