#include <iostream>
#include <juce_dsp/juce_dsp.h>

class OscillatorWrapper {
public:
    OscillatorWrapper(float frequency);
    ~OscillatorWrapper() {}

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);

    void processBlock(juce::AudioBuffer<float>& buffer);

protected:
    float frequency;
private:

    juce::dsp::Oscillator<float> oscillator;
};