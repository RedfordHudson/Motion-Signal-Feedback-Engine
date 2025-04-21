#include "YourPluginName/MainComponent.h"

MainComponent::MainComponent()
{

    std::cout << "testing\n";

    // In the appropriate function or constructor:
    serialPortHandler.openPort("COM3"); // Example COM port, change as needed
    serialPortHandler.startReading();
    
}

MainComponent::~MainComponent()
{
    // serialPortHandler.closePort();  // Close the serial port on destruction


    // Stop reading and close the port on shutdown
    serialPortHandler.stopReading();
    serialPortHandler.closePort();
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
