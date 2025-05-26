#pragma once
#include <juce_core/juce_core.h>

#include <string>
#include <iostream>

// == [ mode: monitor ] ==
#include <windows.h>

// == [ mode: simulate ] ==
#include <random>


class SerialMonitor : public juce::Thread
{
public:
    using Callback = std::function<void(const std::vector<float>)>;

    SerialMonitor(const std::string mode, const int size);
    ~SerialMonitor();

    void start();

    void setCallback(Callback callback);

protected:
    const std::string mode;
    const int size;

private:
    Callback callback;

    void run() override;  // Override run to implement the read loop

    // == [ mode: monitor ] ==

    bool openPort(const std::string& portName);
    void closePort();

    const std::vector<float> readSample();

    HANDLE hSerial = INVALID_HANDLE_VALUE;
    char buffer[256];
    DWORD bytesRead;
    std::string accumulated;

    // == [ mode: simulate ] ==

    const std::vector<float> generateSample();

    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_real_distribution<> dis = std::uniform_real_distribution<>(0.0, 1.0);

};
