// #include <HumanWare.h>
#define JUCE_UNIT_TESTS 1
#include <HumanWareTests.h>

int main()
{
    // Initialize JUCE
    // juce::ScopedJuceInitialiser_GUI juceInit;
    
    // Set up console logging
    // juce::Logger::setCurrentLogger(new juce::FileLogger(juce::File::getSpecialLocation(juce::File::userHomeDirectory)
    //                                                   .getChildFile("test_output.log"), "Test Log"));
    
    juce::UnitTestRunner testRunner;
    std::cout << "Running tests..." << std::endl;
    testRunner.runAllTests();
    std::cout << "Tests complete" << std::endl;

    return 0;
}
