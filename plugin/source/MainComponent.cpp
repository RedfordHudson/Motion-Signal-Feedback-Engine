#include "YourPluginName/MainComponent.h"

MainComponent::MainComponent()
    : AudioAppComponent()  // Call AudioAppComponent constructor
{

    setAudioChannels(0, 2); // <== Needed to start audio: 0 inputs, 2 outputs

    std::cout << "testing\n";

    // cross-thread communication
    // serialPortHandler.setMainComponent(this);

    // sensor
    serialPortHandler.openPort("COM3"); // Example COM port, change as needed
    serialPortHandler.startReading();
    
}

MainComponent::~MainComponent()
{
    // oscillator
    // shutdownAudio(); # <- implicitly called by other library

    // sensor
    serialPortHandler.stopReading();
    serialPortHandler.closePort();
}

// Component Class?

void MainComponent::timerCallback()
{
    // Not used (yet)
}


// GUI ============================================

void MainComponent::paint(juce::Graphics& g)
{
    // g.fillAll(juce::Colours::lightgrey);  // Fill the background with light grey
    g.fillAll(juce::Colours::darkslateblue); // Fill background
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("wtf", juce::Component::getLocalBounds(),
               juce::Justification::centred, true);
 
}

void MainComponent::resized()
{
    // Handle component resizing if necessary
}

// serial ? =====================================

void MainComponent::processData(const juce::String& data)
{
    DBG("Received data: " + data);  // Output the data for debugging purposes
}

// oscillator ============================================


void MainComponent::prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate)
{
    currentSampleRate = sampleRate;
    phase = 0.0;
    phaseIncrement = juce::MathConstants<double>::twoPi * frequency / currentSampleRate;
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // map sensor parameter to oscillator frequency
    // float gxValue = gx.load();
    float gxValue = gx.load();
    float modulatedFrequency = 440.0f + gxValue * 100.0f;  // simple mapping
    phaseIncrement = juce::MathConstants<double>::twoPi * modulatedFrequency / currentSampleRate;


    auto* leftChannel  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    auto* rightChannel = bufferToFill.buffer->getNumChannels() > 1
                         ? bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample)
                         : nullptr;

    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        // Generate a sine wave (you can replace this with a different waveform if desired)
        // float currentSample = std::sin (phase) * 0.25f; // scale down to avoid clipping
        // resolve double->float cast warning message
        float currentSample = static_cast<float>(std::sin(phase)) * 0.25f;


        // Increment the phase
        phase += phaseIncrement;
        if (phase >= juce::MathConstants<double>::twoPi)
            phase -= juce::MathConstants<double>::twoPi;  // Wrap around phase when it completes a cycle

        // Output the sample to the left channel
        leftChannel[sample] = currentSample;

        // Output to the right channel if stereo
        if (rightChannel != nullptr)
            rightChannel[sample] = currentSample;
    }
}


void MainComponent::releaseResources()
{
    // nothing to release
}
