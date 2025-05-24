#include "SerialSimulator.h"

SerialSimulator::SerialSimulator()
    : juce::Thread("SerialSimulator")
{
    startThread();
}

SerialSimulator::~SerialSimulator()
{
    stopThread(1000);
}

void SerialSimulator::setCallback(Callback callback)
{
    this->callback = callback;
}

void SerialSimulator::run()
{
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(-1.0, 1.0);

    while (!threadShouldExit())
    {
        float sample = generateSample();
        callback(sample);
    }
}

double SerialSimulator::generateSample()
{
    juce::Thread::sleep(100);

    // Gene rate a random double between -1.0 and 1.0
    return dis(gen);
}
