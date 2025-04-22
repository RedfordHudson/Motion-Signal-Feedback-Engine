#pragma once
#include <juce_core/juce_core.h>
#include <string>
#include <iostream>
#include <windows.h>

// circular dependency -> error
// #include "YourPluginName/MainComponent.h"

// cross-thread communication
    // forward declaration -> avoid circular dependency
    // tells the compiler that class exists, without providing full details
// class MainComponent;

class SerialPortHandler : public juce::Thread
{
public:
    SerialPortHandler();
    ~SerialPortHandler();

    // cross-thread communication
        // Setter for the callback function
    void setGxCallback(std::function<void(float)> callback);

    void openPort(const std::string& portName);
    void closePort();

    void startReading();  // To start the serial reading thread
    void stopReading();   // To stop the reading loop

    // cross-thread communication
    // void setMainComponent(MainComponent* component)
    // {
    //     mainComponent = component;
    // }


private:
    void run() override;  // Override run to implement the read loop

    bool openSerialPort(const std::string& portName);
    void closeSerialPort();

    HANDLE hSerial = INVALID_HANDLE_VALUE;
    std::atomic<bool> keepReading{false};

    // cross-thread communication
    // MainComponent* mainComponent = nullptr;
    std::function<void(float)> gxCallback;  
};
