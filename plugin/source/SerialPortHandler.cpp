#include "YourPluginName/SerialPortHandler.h"
#include <iostream>
#include <sstream>

SerialPortHandler::SerialPortHandler()
    : hSerial(INVALID_HANDLE_VALUE), keepReading(false) {}

SerialPortHandler::~SerialPortHandler() {
    stopReading();
    closePort();
}

bool SerialPortHandler::openPort(const std::string& portName) {
    std::string fullPortName = "\\\\.\\" + portName;

    hSerial = CreateFileA(
        fullPortName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port: " << portName << std::endl;
        return false;
    }

    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to get current serial parameters.\n";
        return false;
    }

    dcbSerialParams.BaudRate = CBR_115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to set serial parameters.\n";
        return false;
    }

    std::cout << "Successfully opened serial port: " << portName << std::endl;
    return true;
}

void SerialPortHandler::closePort() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
        std::cout << "Serial port closed.\n";
    }
}

void SerialPortHandler::startReading() {
    std::cout << "starting read\n";
    if (keepReading.load()) {
        std::cout << "already reading, closing...\n";
        return;
    }
    std::cout << "setting keepReading to true\n";
    // keepReading = true;
    keepReading.store(true); // Ensure atomic update

    std::cout << "keepReading set to: " << keepReading.load() << std::endl;

    readThread = std::thread(&SerialPortHandler::readLoop, this);


    // Check if the thread is created properly
    if (readThread.joinable()) {
        std::cout << "Thread successfully created and joinable\n";
    } else {
        std::cerr << "Failed to create thread or thread is not joinable\n";
    }
}

void SerialPortHandler::readLoop() {
    std::cout << "readloop started\n";

    std::cout << "keepReading set to: " << keepReading.load() << std::endl;
    keepReading.store(true);  // Ensure keepReading is true when we start the loop
    std::cout << "keepReading set to: " << keepReading.load() << std::endl;

    char buffer[256];
    std::cout << "keepReading set to: " << keepReading.load() << std::endl;
    DWORD bytesRead;
    std::string accumulated;

    std::cout << "keepReading set to: " << keepReading.load() << std::endl;
    while (keepReading.load()) {
        std::cout << "keepReading in loop: " << keepReading.load() << std::endl;
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
            buffer[bytesRead] = '\0';
            accumulated += std::string(buffer, bytesRead);

            size_t newlinePos;
            while ((newlinePos = accumulated.find('}')) != std::string::npos) {
                std::string completeMsg = accumulated.substr(0, newlinePos + 1);
                accumulated.erase(0, newlinePos + 1);

                std::cout << "Received: " << completeMsg << std::endl;
            }
        } else {
            std::cerr << "Failed to read from serial port.\n";
            break;
        }

        Sleep(10); // Small delay to avoid overloading CPU
    }
}


void SerialPortHandler::stopReading() {
    if (keepReading.load()) {
        keepReading = false;
        if (readThread.joinable())
            readThread.join();
    }
}