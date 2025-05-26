#include <JuceHeader.h>
#include <TestComponent.h>
// #include <AudioTestComponent.h>

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow() : DocumentWindow("Test App", juce::Colours::black, DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new TestComponent(), true);
        // setContentOwned(new AudioTestComponent(), true);
        centreWithSize(800, 600);
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        juce::JUCEApplication::quit();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

class TestApplication : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Test App"; }
    const juce::String getApplicationVersion() override { return "1.0.0"; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String&) override
    {
        mainWindow.reset(new MainWindow());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(TestApplication)
