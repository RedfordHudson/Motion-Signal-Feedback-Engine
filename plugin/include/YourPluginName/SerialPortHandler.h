#pragma once
#include <juce_core/juce_core.h>
#include <string>
#include <iostream>
#include <windows.h>

class SerialPortHandler : public juce::Thread
{
public:
    SerialPortHandler();
    ~SerialPortHandler();

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
};
