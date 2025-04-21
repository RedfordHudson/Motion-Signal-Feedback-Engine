#pragma once

#include <windows.h>
#include <string>
#include <thread>
#include <atomic>

class SerialPortHandler
{
public:
    SerialPortHandler();
    ~SerialPortHandler();

    bool openPort(const std::string& portName);
    void closePort();

    void startReading();
    void stopReading();

private:
    HANDLE hSerial;
    std::atomic<bool> keepReading;
    std::thread readThread;

    void readLoop();
};
