#include <juce_core/juce_core.h>
#include <iostream>

class Ware {
    public:
        Ware() {};
        ~Ware() {};

        void test() {
            std::cout << "working!" << std::endl;
        }
};