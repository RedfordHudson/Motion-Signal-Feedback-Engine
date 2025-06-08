#include "OscillatorWrapper.h"

OscillatorWrapper::OscillatorWrapper(float frequency)
    : frequency(frequency)
{
    oscillator.initialise( [](float x) {return std::sin(x); } );
    oscillator.setFrequency(frequency);
    
    // Envelope parameters (in seconds / normalized)
    envelopeParams.attack  = 0.008f;
    envelopeParams.decay   = 0.08f;
    envelopeParams.sustain = 0.0f;
    envelopeParams.release = 0.1f;
    envelope.setParameters(envelopeParams);
}

void OscillatorWrapper::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    // propagates audio engine configuration to JUCE DSP objects
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlockExpected;
    spec.sampleRate = sampleRate;
    spec.numChannels = 2;

    oscillator.prepare(spec);

    envelope.setSampleRate(sampleRate);
}

void OscillatorWrapper::processBlock(juce::AudioBuffer<float>& buffer, const int beatSampleIndex) {
    
    // wrapper for buffer; makes buffer operations easier for DSP objects
    juce::dsp::AudioBlock<float> audioBlock(buffer);
    // configure DSP block to overwrite input ("replacing")
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    oscillator.process(context);

    applyEnvelope(buffer, beatSampleIndex);
}

void OscillatorWrapper::applyEnvelope(juce::AudioBuffer<float>& buffer, const int beatSampleIndex) {
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* samples = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            if (sample == beatSampleIndex)
                envelope.noteOn();

            float env = envelope.getNextSample();  // 0..1
            samples[sample] *= env * gain;
        }
    }
}