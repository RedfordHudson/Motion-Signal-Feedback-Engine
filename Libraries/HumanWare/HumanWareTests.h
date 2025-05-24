#include <juce_core/juce_core.h>
#include <iostream>
#include <HumanWare.h>

class HumanWareTests : public juce::UnitTest {
    public:
        HumanWareTests() : juce::UnitTest("HumanWareTests") {};
        ~HumanWareTests() override = default;

        void runTest() override {
            beginTest("Basic Test");
            expectEquals(1, 0, "Basic equality test");
        }

    private:
        std::string sample = "{flex:1}";
};