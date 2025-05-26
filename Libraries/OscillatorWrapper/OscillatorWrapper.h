#include <iostream>
#include <juce_dsp/juce_dsp.h>

class OscillatorWrapper {
public:
    OscillatorWrapper(float frequency);
    ~OscillatorWrapper() {}

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);

    void processBlock(juce::AudioBuffer<float>& buffer, const int beatSampleIndex);

    void applyEnvelope(juce::AudioBuffer<float>& buffer, const int beatSampleIndex);

protected:
    float frequency;
private:
    juce::dsp::Oscillator<float> oscillator;

    juce::ADSR envelope;
    juce::ADSR::Parameters envelopeParams;
};