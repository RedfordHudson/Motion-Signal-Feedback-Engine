#include "OscillatorWrapper.h"

OscillatorWrapper::OscillatorWrapper(float frequency)
    : frequency(frequency)
{
    oscillator.initialise( [](float x) {return std::sin(x); } );
    oscillator.setFrequency(frequency);
}

void OscillatorWrapper::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    // propagates audio engine configuration to JUCE DSP objects
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlockExpected;
    spec.sampleRate = sampleRate;
    spec.numChannels = 2;

    oscillator.prepare(spec);
}

void OscillatorWrapper::processBlock(juce::AudioBuffer<float>& buffer) {
    
    // wrapper for buffer; makes buffer operations easier for DSP objects
    juce::dsp::AudioBlock<float> audioBlock(buffer);
    // configure DSP block to overwrite input ("replacing")
    juce::dsp::ProcessContextReplacing<float> context(audioBlock);
    oscillator.process(context);
}