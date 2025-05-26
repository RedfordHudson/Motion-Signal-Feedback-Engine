#include <juce_core/juce_core.h>
#include <HumanWare.h>
// #include <SensorWare.h>
// #include <iostream>

class HumanWareTests : public juce::UnitTest {
public:
    HumanWareTests() : juce::UnitTest("HumanWareTests") {};
    ~HumanWareTests() override = default;

    void runTest() override {
        beginTest("Testing SensorWare");

        testFlexSensor();
        testGyroscope();

        beginTest("Testing HumanWare");

        testFingerVector();
        testHand();
        // testBody();
    }

    void testFlexSensor() {
        FlexSensor flex;
        std::vector<float> sample = {1.0};
        flex.processSample(sample);
        
        expectEquals(flex.getSize(), 1, "Gyro Size");
        expectEquals(flex.getValue("x"), (float)1.0, "Flex State Capture");
        expect(vectorsAreEqual(flex.generateDecoderKey(),{"x"}), "Flex Decoder");
    }

    void testGyroscope() {
        Gyroscope gyro;
        std::vector<float> sample = {1.0,2.0,3.0};
        gyro.processSample(sample);
        
        expectEquals(gyro.getSize(), 3, "Gyro Size");
        expectEquals(gyro.getValue("x"), (float)1.0, "Gyro State Capture");
        expectEquals(gyro.getValue("y"), (float)2.0, "Gyro State Capture");
        expectEquals(gyro.getValue("z"), (float)3.0, "Gyro State Capture");
        expect(vectorsAreEqual(gyro.generateDecoderKey(),{"x","y","z"}), "Gyro Decoder");
    }

    void testFingerVector() {
        FingerVector fv(2);
        std::vector<float> sample = {1.0,2.0};
        fv.processSample(sample);

        expectEquals(fv.getSize(), 2, "Finger Vector Size");
        expectEquals(fv.getChild("0")->getValue("x"), (float)1.0, "Finger Vector State Capture");
        expectEquals(fv.getChild("1")->getValue("x"), (float)2.0, "Finger Vector State Capture");
        expect(vectorsAreEqual(fv.generateDecoderKey(),{"0/flex/x","1/flex/x"}), "Finger Vector Decoder");
    }

    void testHand() {
        Hand hand;
        std::vector<float> sample = {1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
        hand.processSample(sample);

        expectEquals(hand.getSize(), 8, "Hand Size");
        expectEquals(hand.getChild("gyro")->getValue("x"), (float)1.0, "Hand State Capture");
        expectEquals(hand.getChild("gyro")->getValue("y"), (float)2.0, "Hand State Capture");
        expectEquals(hand.getChild("gyro")->getValue("z"), (float)3.0, "Hand State Capture");
        expectEquals(hand.getChild("accel")->getValue("x"), (float)4.0, "Hand State Capture");
        expectEquals(hand.getChild("accel")->getValue("y"), (float)5.0, "Hand State Capture");
        expectEquals(hand.getChild("accel")->getValue("z"), (float)6.0, "Hand State Capture");
        expectEquals(hand.getChild("fv")->getChild("0")->getValue("x"), (float)7.0, "Hand State Capture");
        expectEquals(hand.getChild("fv")->getChild("1")->getValue("x"), (float)8.0, "Hand State Capture");
        expect(vectorsAreEqual(hand.generateDecoderKey(),
            {"gyro/x","gyro/y","gyro/z",
            "accel/x","accel/y","accel/z",
            "fv/0/flex/x","fv/1/flex/x"}),
             "Hand Decoder");
    }

    void testBody() {
        Body body;
        std::vector<float> sample = {1.0};
        body.processSample(sample);

        expectEquals(body.getSize(), 1, "Body Size");
        expectEquals(body.getChild("flex")->getValue("x"), (float)1.0, "Body State Capture");
    }

private:
    bool vectorsAreEqual(const std::vector<std::string>& a, const std::vector<std::string>& b)
    {
        if (a.size() != b.size())
            return false;
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i] != b[i])
                return false;
        return true;
    }

};

// Global instance (JUCE relies on this object being registered before test run)
static HumanWareTests humanWareTest;


        // std::string sample = "1,2,3,1,2,3,1,2";
        // std::vector<float> sample = {1, 2, 3, 1, 2, 3, 1, 2};