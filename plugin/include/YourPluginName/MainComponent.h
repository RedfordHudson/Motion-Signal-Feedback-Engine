// MainComponent.h

#pragma once  // or use traditional guards: #ifndef MAIN_COMPONENT_H, #define MAIN_COMPONENT_H, etc.

// GUI
#include <juce_gui_basics/juce_gui_basics.h>

// oscillator
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

// sensor
// #include "YourPluginName/SerialPortHandler.h"
class SerialPortHandler;

// cross-thread communication
#include <atomic>

class MainComponent  : public juce::Timer,
                    //    public juce::Component, # <- redundant
                       public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    // Component Class?
    // Override timerCallback but not as pure virtual (remove "= 0")
    void timerCallback() override;

    // GUI
    void paint(juce::Graphics&) override;
    void resized() override;

    // oscillator
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill);
    // must override releaseResources() because it's declared as a pure virtual function in the base class
    void releaseResources() override;

    // cross-thread communication
    // inline member function; compiler "inlines" it for performance
    void setGx(float newGx) { gx.store(newGx); }

private:

    // oscillator
    double currentSampleRate = 0.0;
    double phase = 0.0;
    double phaseIncrement = 0.0;
    float frequency = 440.0f; // A4

    std::atomic<float> gx = 0.0f;  // shared between threads

    // sensor
        // include -> class instantiation
    // SerialPortHandler serialPortHandler;
        // forward declaration -> pointer
    std::unique_ptr<SerialPortHandler> serialPortHandler;

    void processData(const juce::String& data);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
