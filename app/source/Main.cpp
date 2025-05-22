#include <JuceHeader.h>

class MainComponent : public juce::Component
{
public:
    MainComponent()
    {
        setSize(800, 600);
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
    }

    void resized() override
    {
    }
};

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow() : DocumentWindow("Synth Engine", juce::Colours::black, DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);
        centreWithSize(800, 600);
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

class Application : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Synth Engine"; }
    const juce::String getApplicationVersion() override { return "1.0.0"; }

    void initialise(const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow>();
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(Application) 