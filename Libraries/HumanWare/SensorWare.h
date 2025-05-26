#include <juce_core/juce_core.h>

// === TIER 0: base abstract WareNode class ===

class WareNode {
public:
    WareNode(const std::string& name) : name(name) {};
    virtual ~WareNode() = default;

    virtual void processSample(const std::vector<float>& sample) = 0;

    // const before -> return type
    // const after -> does not modify object
    virtual const int getSize() const = 0;

    virtual const std::vector<std::string> generateDecoderKey() const = 0;

    // only used in SensorWareNodes
    virtual const float getValue(const std::string& key) const = 0;
    virtual const juce::NamedValueSet& getState() const = 0;


    // only used in HumanWareNodes
    virtual std::shared_ptr<WareNode> getChild(const std::string& name) const = 0;

    const std::string getName() const { return name; }

protected:
    std::string name; // allows variable to be passed through to constructor
};

// === TIER 1: abstract SensorWareNode class ===

class SensorWareNode : public WareNode {
public:
    SensorWareNode(const std::string& name) : WareNode(name) {};

    const juce::NamedValueSet& getState() const override {
        return state;
    }

    void processSample(const std::vector<float>& sample) override {

        // assert that sample and key size are equal
        jassert(sample.size() == getSize());

        // map sample elements to keys
        for (size_t i = 0; i < sample.size(); ++i) {
            state.set(juce::Identifier(getKeys()[i]), sample[i]);
        }
    }
    
    const float getValue(const std::string& key) const override {
        jassert(std::find(getKeys().begin(), getKeys().end(), key) != getKeys().end());
        return static_cast<float>(state[juce::Identifier(key)]);
    }

    const int getSize() const override {
        return getKeys().size();
    }

    const std::vector<std::string> generateDecoderKey() const override {
        return getKeys();
    }

    std::shared_ptr<WareNode> getChild(const std::string& name) const override { return nullptr; }
    
protected:
    juce::NamedValueSet state; // any class that inherits from WareNode can directly access and modify state
    virtual const std::vector<std::string>& getKeys() const = 0;
};

// === TIER 2: abstract sensor type classes ===

class ScalarSensorWareNode : public SensorWareNode {
public:
    ScalarSensorWareNode(const std::string& name) : SensorWareNode(name) {};

protected:
    const std::vector<std::string>& getKeys() const override {
        static const std::vector<std::string> keys = { "x" };
        return keys;
    }
};

class SpatialSensorWareNode : public SensorWareNode {
public:
    SpatialSensorWareNode(const std::string& name) : SensorWareNode(name) {};

protected:
    const std::vector<std::string>& getKeys() const override {
        static const std::vector<std::string> keys = { "x", "y", "z" };
        return keys;
    }
};

// === TIER 3: concrete sensor classes ===

class FlexSensor : public ScalarSensorWareNode {
public:
    static constexpr const char* typeName = "flex";
    FlexSensor() : ScalarSensorWareNode(typeName) {};
};

class Gyroscope : public SpatialSensorWareNode {
public:
    static constexpr const char* typeName = "gyro";
    Gyroscope() : SpatialSensorWareNode(typeName) {};
};

class Accelerometer : public SpatialSensorWareNode {
public:
    static constexpr const char* typeName = "accel";
    Accelerometer() : SpatialSensorWareNode(typeName) {};
};