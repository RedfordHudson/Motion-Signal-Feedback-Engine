#include <iostream>
#include <juce_dsp/juce_dsp.h>

class OscillatorWrapper {
public:
    OscillatorWrapper(const float BASE_FREQUENCY);
    ~OscillatorWrapper() {}

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);

    void processBlock(juce::AudioBuffer<float>& buffer, const int beatSampleIndex);

    void applyEnvelope(juce::AudioBuffer<float>& buffer, const int beatSampleIndex);

    void modulateFrequency(const float ratio);

protected:
    float BASE_FREQUENCY;
private:
    juce::dsp::Oscillator<float> oscillator;

    juce::ADSR envelope;
    juce::ADSR::Parameters envelopeParams;

    const float gain = 0.1f;
};