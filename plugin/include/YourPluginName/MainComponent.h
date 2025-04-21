// MainComponent.h

#pragma once  // or use traditional guards: #ifndef MAIN_COMPONENT_H, #define MAIN_COMPONENT_H, etc.

#include <juce_gui_basics/juce_gui_basics.h>
#include "YourPluginName/SerialPortHandler.h"

class MainComponent  : public juce::Component,
                       public juce::Timer
{
public:
    MainComponent();
    ~MainComponent() override;

    void timerCallback() override;
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SerialPortHandler serial();
    void processData(const juce::String& data);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
