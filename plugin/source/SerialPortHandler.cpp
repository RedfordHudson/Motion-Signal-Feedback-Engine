#include "YourPluginName/SerialPortHandler.h"

SerialPortHandler::SerialPortHandler() : Thread("Serial Port Handler") {
    // Constructor body if needed
}

SerialPortHandler::~SerialPortHandler() {
    stopReading();
    closePort();
}

bool SerialPortHandler::openSerialPort(const std::string& portName) {
    hSerial = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port: " << portName << std::endl;
        return false;
    }
    
    // Configure the serial port (baud rate, byte size, etc.)
    DCB dcbSerialParams = {0};
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to get serial port state.\n";
        closePort();
        return false;
    }
    
    dcbSerialParams.BaudRate = CBR_115200;  // Set baud rate
    dcbSerialParams.ByteSize = 8;          // 8 data bits
    dcbSerialParams.StopBits = ONESTOPBIT; // 1 stop bit
    dcbSerialParams.Parity   = NOPARITY;   // No parity
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Failed to set serial port state.\n";
        closePort();
        return false;
    }

    return true;
}

void SerialPortHandler::closeSerialPort() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
    }
}

void SerialPortHandler::openPort(const std::string& portName) {
    if (!openSerialPort(portName)) {
        std::cerr << "Unable to open port.\n";
    } else {
        std::cout << "Successfully opened serial port: " << portName << std::endl;
    }
}

void SerialPortHandler::closePort() {
    stopReading();  // Ensure the reading thread is stopped before closing the port
    closeSerialPort();
}

void SerialPortHandler::startReading() {
    std::cout << "startReading\n";
    if (!isThreadRunning()) {
        startThread();  // Starts the read loop in a background thread
    }
}

void SerialPortHandler::stopReading() {
    keepReading.store(false);
    stopThread(2000);  // Stop the thread with a timeout (2 seconds)
}

void SerialPortHandler::run() {
    std::cout << "running\n";

    keepReading.store(true);
    std::cout << "keepReading: "<<keepReading<<"\n";

    char buffer[256];
    DWORD bytesRead;
    std::string accumulated;

    while (keepReading.load()) {
        std::cout << "entering read loop\n";
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
            std::cout << "passed if statement\n";

            
            // for (size_t i = 0; i < bytesRead; ++i) {
            //     std::cout << "Byte " << i << ": " << static_cast<int>(buffer[i]) << std::endl;
            // }

            buffer[bytesRead] = '\0';
            accumulated += std::string(buffer, bytesRead);
            std::cout << "accumulated: "<<accumulated<<"\n\n";

            size_t newlinePos;
            while ((newlinePos = accumulated.find('}')) != std::string::npos) {
                std::cout << "entering NESTED read loop\n";

                std::string completeMsg = accumulated.substr(0, newlinePos + 1);
                std::cout << "--1";
                accumulated.erase(0, newlinePos + 1);
                std::cout << "--2";
                std::cout << "accumulated: "<<accumulated<<"\n";

                std::cout << "Received: " << completeMsg << std::endl;
            }
        } else {
            std::cerr << "Failed to read from serial port.\n";
            break;
        }

        Sleep(10); // Small delay to avoid overloading the CPU
    }
}
