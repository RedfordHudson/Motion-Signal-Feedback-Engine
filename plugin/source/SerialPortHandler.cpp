#include "YourPluginName/SerialPortHandler.h"
#include <iostream>

SerialPortHandler::SerialPortHandler() : hSerial(INVALID_HANDLE_VALUE) {}

SerialPortHandler::~SerialPortHandler() {
    // Close the serial port handle if it's valid
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
    }
}

bool SerialPortHandler::openPort(const std::string& portName) {
    // Open the specified serial port
    hSerial = CreateFile(
        portName.c_str(),               // port name (e.g., "COM3" or "\\\\.\\COM3")
        GENERIC_READ | GENERIC_WRITE,    // read/write access
        0,                              // no sharing
        NULL,                           // default security attributes
        OPEN_EXISTING,                  // open an existing port
        0,                              // no attributes
        NULL                            // no template
    );

    // Check if the port was successfully opened
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port: " << portName << std::endl;
        return false;
    }

    std::cout << "Successfully opened serial port: " << portName << std::endl;
    return true;
}
