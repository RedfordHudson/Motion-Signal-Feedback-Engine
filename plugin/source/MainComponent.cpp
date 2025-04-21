#include "YourPluginName/MainComponent.h"

MainComponent::MainComponent()
{

    std::cout << "testing\n";

        // Inside MainComponent:
    SerialPortHandler serial;

    // In the appropriate function or constructor:
    bool isOpen = serial.openPort("COM3"); // Example COM port, change as needed


    // serialPortHandler.openPort("COM3");  // Open the serial port
    // startTimer(100);  // Start the timer to read data every 100ms
}

MainComponent::~MainComponent()
{
    // serialPortHandler.closePort();  // Close the serial port on destruction
}

void MainComponent::timerCallback()
{
    // auto data = serialPortHandler.readData();  // Read data from the serial port
    // if (!data.isEmpty())
    // {
    //     processData(data);  // Process the data
    // }
}

void MainComponent::paint(juce::Graphics& g)
{
    // g.fillAll(juce::Colours::lightgrey);  // Fill the background with light grey
    g.fillAll(juce::Colours::darkslateblue); // Fill background
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("wtf", getLocalBounds(),
               juce::Justification::centred, true);
 
}

void MainComponent::resized()
{
    // Handle component resizing if necessary
}

void MainComponent::processData(const juce::String& data)
{
    DBG("Received data: " + data);  // Output the data for debugging purposes
}
