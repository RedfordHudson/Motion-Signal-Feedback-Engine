#include "MainComponent.h"
// #include "SerialPortHandler.h"

MainComponent::MainComponent()
    : AudioAppComponent()  // Call AudioAppComponent constructor
{
    setAudioChannels(0, 2); // <== Needed to start audio: 0 inputs, 2 outputs
    std::cout << "testing\n";

    // if (readSensorData) {
    //     std::cout << "attempting to open port\n";
    //     // forward declaration -> instantiate pointer
    //     serialPortHandler = std::make_unique<SerialPortHandler>();

    //     // Set the callback function for gx
    //     serialPortHandler->setGxCallback([this](float gxValue) {
    //         setGx(gxValue);  // Call setGx to update the gx value in MainComponent
    //     });

    //     serialPortHandler->openPort("COM3"); // Example COM port, change as needed
    //     serialPortHandler->startReading();
    // }
}

MainComponent::~MainComponent()
{
    // if (readSensorData) {
    //     serialPortHandler->stopReading();
    //     serialPortHandler->closePort();
    // }
}

void MainComponent::timerCallback()
{
    // Not used (yet)
}

// GUI ============================================

void MainComponent::paint(juce::Graphics& g)
{
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

// oscillator ============================================

void MainComponent::prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate)
{
    currentSampleRate = sampleRate;
    phase = 0.0;
    phaseIncrement = juce::MathConstants<double>::twoPi * baseFrequency / currentSampleRate;
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // if (readSensorData) {
    //     // map sensor parameter to oscillator frequency
    //     float gxValue = gx.load();
    //     // std::cout << gxValue << "\n";

    //     // Normalize gx to the desired frequency range (20 Hz to 2000 Hz)
    //     float gx_min = -2000.0f;  // Example minimum value (adjust to your data)
    //     float gx_max = 2000.0f;   // Example maximum value (adjust to your data)

    //     // Normalize gx to a value between 0 and 1
    //     float normalizedGx = (gxValue - gx_min) / (gx_max - gx_min);
    //     // Map it to the frequency range
    //     baseFrequency *= normalizedGx;

    //     phaseIncrement = juce::MathConstants<double>::twoPi * baseFrequency / currentSampleRate;
    // }

    auto* leftChannel  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    auto* rightChannel = bufferToFill.buffer->getNumChannels() > 1
                         ? bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample)
                         : nullptr;

    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
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
