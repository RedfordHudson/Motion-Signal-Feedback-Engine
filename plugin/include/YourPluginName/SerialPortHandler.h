#pragma once

#include <windows.h>
#include <string>

class SerialPortHandler
{
public:
    SerialPortHandler();
    ~SerialPortHandler();

    bool openPort(const std::string& portName);
    void closePort();
    void readSerialData();

private:
    HANDLE hSerial;
    bool isPortOpen;
};
