#include <juce_core/juce_core.h>
#include <random>

class SerialSimulator : public juce::Thread
{
    public:
        using Callback = std::function<void(float)>;

        SerialSimulator();
        ~SerialSimulator();

        void run() override;
        void setCallback(Callback callback);

        double generateSample();
    private:

        Callback callback;

        std::random_device rd;
        std::mt19937 gen;
        std::uniform_real_distribution<> dis;
};
