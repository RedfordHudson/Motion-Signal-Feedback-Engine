#ifndef SERIALPORTHANDLER_H
#define SERIALPORTHANDLER_H

#include <string>
#include <Windows.h>

class SerialPortHandler {
public:
    // Constructor
    SerialPortHandler();

    // Destructor
    ~SerialPortHandler();

    // Open a serial port by name (e.g., "COM3" or "\\\\.\\COM3")
    bool openPort(const std::string& portName);

private:
    // Handle to the serial port
    HANDLE hSerial;
};

#endif // SERIALPORTHANDLER_H
