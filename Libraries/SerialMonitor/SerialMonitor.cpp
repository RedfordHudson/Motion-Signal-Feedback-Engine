#include "SerialMonitor.h"

SerialMonitor::SerialMonitor(const std::string mode, const int size)
    : mode(mode), size(size),
    Thread("Serial Monitor")
{}

SerialMonitor::~SerialMonitor() {
    stopThread(1000);
    if (mode == "monitor")
        closePort();
}

void SerialMonitor::start() {
    if (mode == "monitor" && !openPort("COM3"))
        return;
    startThread();
}

bool SerialMonitor::openPort(const std::string& portName) {
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
        std::cerr << "Unable to open port.\n";
        closePort();
        return false;
    }

    std::cout << "Successfully opened serial port: " << portName << std::endl;
    return true;
}

void SerialMonitor::closePort() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = INVALID_HANDLE_VALUE;
    }
}

void SerialMonitor::guardedCallback(const std::vector<float> sample) {
    if(sample.size() != size) {
        std::cout << "SerialMonitor: incorrectly sized samples: " << std::to_string(size) << " =/= " << std::to_string(sample.size()) << " | ";
        for(const auto& value : sample) {
            std::cout << value << ",";
        }
        std::cout << std::endl;
    }
    else
        callback(sample);
}

void SerialMonitor::setCallback(Callback callback)
{
    this->callback = callback;
}

void SerialMonitor::run() {
    while (!threadShouldExit()) {
        
        char buffer[256];
        DWORD bytesRead;

        if (mode == "monitor") {
            // DWORD bytesRead = 0;
            
            // Read all available data in one go
            if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, nullptr) && bytesRead > 0) {
                buffer[bytesRead] = '\0';
                accumulated += std::string(buffer, bytesRead);

                // Process all complete messages in the buffer
                size_t newlinePos;
                while ((newlinePos = accumulated.find('\n')) != std::string::npos) {
                    std::string completeMsg = accumulated.substr(0, newlinePos);
                    accumulated.erase(0, newlinePos + 1);

                    const std::vector<float> sample = vectorizeString(completeMsg);
                    guardedCallback(sample);
                }
            } else {
                std::cerr << "Failed to read from serial port.\n";
                break;
            }
        }
        else if (mode == "simulate") {
            guardedCallback(generateSample());
            wait(10);
        }

        wait(1); // Reduced delay for faster response
    }
}

// == [ mode: monitor ] ==

static std::vector<float> vectorizeString(const std::string& completeMsg) {
    std::vector<float> values;
    std::stringstream ss(completeMsg);
    std::string value;
    
    while (std::getline(ss, value, ',')) {
        try {
            values.push_back(std::stof(value));
        } catch (const std::exception& e) {
            std::cerr << "Error parsing value: " << value << std::endl;
        }
    }
    
    return values;
}


// == [ mode: simulate ] ==

const std::vector<float> SerialMonitor::generateSample()
{
    std::vector<float> sample(size);
    for (int i = 0; i < size; i++) {
        // Generate random floats between -1.0 and 1.0
        sample[i] = static_cast<float>(dis(gen));
    }

    return sample;
}