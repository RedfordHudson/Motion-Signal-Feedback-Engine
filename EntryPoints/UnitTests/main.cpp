#include <juce_core/juce_core.h>
#include <iostream>
#include <memory>
#include <HumanWareTests.h>

// Custom logger that redirects to stdout
class StdoutLogger : public juce::Logger {
    void logMessage(const juce::String& message) override {
        std::cout << message << std::endl;
    }
};

int main() {
    // Set up logger so JUCE logs go to stdout
    auto logger = std::make_unique<StdoutLogger>();
    juce::Logger::setCurrentLogger(logger.get());

    // Run all tests (with verbose = true)
    juce::UnitTestRunner runner;
    runner.runAllTests(true);

    return 0;
}
