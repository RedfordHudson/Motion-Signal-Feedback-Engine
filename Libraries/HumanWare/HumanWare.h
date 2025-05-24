#include <juce_core/juce_core.h>
#include <iostream>

class Ware {
    public:
        Ware() {};
        ~Ware() {};

        void processSample(double sample) {
            state.set("x", sample);
        }
    private:
        juce::NamedValueSet state;
        // std::string name = "x";
};