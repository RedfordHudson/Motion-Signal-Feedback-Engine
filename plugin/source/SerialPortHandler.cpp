#include "YourPluginName/SerialPortHandler.h"
#include <iostream>

SerialPortHandler::SerialPortHandler() : hSerial(INVALID_HANDLE_VALUE), isPortOpen(false) {}

SerialPortHandler::~SerialPortHandler()
{
    closePort();
}

bool SerialPortHandler::openPort(const std::string& portName)
{
    std::string fullName = "\\\\.\\" + portName;
    hSerial = CreateFileA(
        fullName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr);

    if (hSerial == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to open serial port: " << portName << std::endl;
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        std::cerr << "Failed to get current serial parameters" << std::endl;
        closePort();
        return false;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams))
    {
        std::cerr << "Failed to set serial parameters" << std::endl;
        closePort();
        return false;
    }

    isPortOpen = true;
    std::cout << "Successfully opened serial port: " << portName << std::endl;
    return true;
}

void SerialPortHandler::closePort()
{
    if (isPortOpen && hSerial != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        isPortOpen = false;
        std::cout << "Serial port closed." << std::endl;
    }
}

void SerialPortHandler::readSerialData()
{
    if (!isPortOpen) return;

    char buffer[128];
    DWORD bytesRead;

    BOOL result = ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, nullptr);
    if (result && bytesRead > 0)
    {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer
        std::cout << "Received: " << buffer << std::endl;
    }
    else
    {
        std::cerr << "No data or read error" << std::endl;
    }
}
