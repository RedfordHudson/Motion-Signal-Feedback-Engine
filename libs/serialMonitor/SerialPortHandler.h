#pragma once
#ifndef JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED
#define JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED 1
#endif

#include <juce_core/juce_core.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <functional>

class SerialPortHandler : public juce::Thread
{
public:
    SerialPortHandler();
    ~SerialPortHandler();

    void setGxCallback(std::function<void(float)> callback);
    void openPort(const std::string& portName);
    void closePort();
    void startReading();  // To start the serial reading thread
    void stopReading();   // To stop the reading loop

private:
    void run() override;  // Override run to implement the read loop
    bool openSerialPort(const std::string& portName);
    void closeSerialPort();

    HANDLE hSerial = INVALID_HANDLE_VALUE;
    std::atomic<bool> keepReading{false};
    std::function<void(float)> gxCallback;
};
