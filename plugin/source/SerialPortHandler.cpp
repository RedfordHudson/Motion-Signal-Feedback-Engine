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
    if (!isThreadRunning()) {
        startThread();  // Starts the read loop in a background thread
    }
}

void SerialPortHandler::stopReading() {
    keepReading.store(false);
    stopThread(2000);  // Stop the thread with a timeout (2 seconds)
}


std::unordered_map<std::string, int> parseJsonToDict(const std::string& completedMsg) {
    std::unordered_map<std::string, int> data;
    
    // Remove the curly braces from the string
    std::string msg = completedMsg.substr(1, completedMsg.size() - 2);
    
    // Create a stringstream to read the data
    std::stringstream ss(msg);
    std::string keyValue;
    
    // Loop through the stringstream and extract key-value pairs
    while (std::getline(ss, keyValue, ',')) {
        // Trim leading and trailing spaces (if any)
        keyValue.erase(0, keyValue.find_first_not_of(" \t"));
        keyValue.erase(keyValue.find_last_not_of(" \t") + 1);
        
        // Find the colon separating key and value
        size_t colonPos = keyValue.find(":");
        
        if (colonPos != std::string::npos) {
            // Extract key and value as strings
            std::string key = keyValue.substr(0, colonPos);
            std::string valueStr = keyValue.substr(colonPos + 1);
            
            // Remove any extra spaces and quotation marks
            key.erase(0, key.find_first_not_of("\" \t"));
            key.erase(key.find_last_not_of("\" \t") + 1);
            
            valueStr.erase(0, valueStr.find_first_not_of(" \t"));
            valueStr.erase(valueStr.find_last_not_of(" \t") + 1);
            
            // Convert the value string to an integer
            int value = std::stoi(valueStr);
            
            // Insert the key-value pair into the unordered_map
            data[key] = value;
        }
    }
    
    return data;
}

void stringifyMap(std::unordered_map<std::string, int>& result) {
    for (const auto& pair : result) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void SerialPortHandler::run() {

    keepReading.store(true);

    char buffer[256];
    DWORD bytesRead;
    std::string accumulated;

    while (keepReading.load()) {
        if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {

            buffer[bytesRead] = '\0';
            accumulated += std::string(buffer, bytesRead);

            size_t newlinePos;
            while ((newlinePos = accumulated.find('}')) != std::string::npos) {

                std::string completeMsg = accumulated.substr(0, newlinePos + 1);
                accumulated.erase(0, newlinePos + 1);

                std::unordered_map<std::string, int> result = parseJsonToDict(completeMsg);

                /*
                dictionary structure {
                    'ax':int,
                    'ay':int,
                    'az':int,
                    'gx':int,
                    'gy':int,
                    'gz':int,
                }
                */

                std::cout << result["gx"] << std::endl;
            
            }
        } else {
            std::cerr << "Failed to read from serial port.\n";
            break;
        }

        Sleep(10); // Small delay to avoid overloading the CPU
    }
}
