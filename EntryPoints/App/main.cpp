#include <JuceHeader.h>

#if defined(TEST_GRAPHICS)
    #include <GraphicsTester.h>
#elif defined(TEST_AUDIO)
    #include <AudioTester.h>
#elif defined(BUILD_MAIN)
    #include <MainComponent.h>
#else
    #error No component mode defined
#endif


class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow() : DocumentWindow("Test App", juce::Colours::black, DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);

        #if defined(TEST_GRAPHICS)
            setContentOwned(new GraphicsTester(), true);
        #elif defined(TEST_AUDIO)
            setContentOwned(new AudioTester(), true);
        #elif defined(BUILD_MAIN)
            setContentOwned(new MainComponent(), true);
        #else
            #error No component mode defined
        #endif

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
