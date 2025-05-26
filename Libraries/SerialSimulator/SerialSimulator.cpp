#include "SerialSimulator.h"

SerialSimulator::SerialSimulator()
    : juce::Thread("SerialSimulator")
{
    // startThread();
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
    dis = std::uniform_real_distribution<>(0.0, 1.0);

    while (!threadShouldExit())
    {
        const std::vector<float> sample = generateSample();

        if (!callback)
        {
            std::cout << "callback is undefined!" << std::endl;
            break;
        }

        callback(sample);
    }
}

const std::vector<float> SerialSimulator::generateSample()
{
    juce::Thread::sleep(100);

    // Gene rate a random float between -1.0 and 1.0
    float sample = static_cast<float>(dis(gen));

    return {sample};
}
