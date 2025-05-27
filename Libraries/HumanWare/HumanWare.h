#include "SensorWare.h"
#include <vector>
#include <utility>
#include <algorithm>

// === TIER 1: abstract HumanWare classes ===

class HumanWareNode : public WareNode {
public:
    HumanWareNode(const std::string& name) : WareNode(name) {};

    void addChild(std::string name, std::shared_ptr<WareNode> child) {
        children.emplace_back(name, child);
    }

    std::shared_ptr<WareNode> getChild(const std::string& name) const override {
        auto it = std::find_if(children.begin(), children.end(),
            [&name](const auto& pair) { return pair.first == name; });
        jassert(it != children.end());
        return it->second;
    }

    const int getSize() const override {
        int size = 0;
        for (const auto& [child_name, child] : children)
            size += child->getSize();
        return size;
    }

    void processSample(const std::vector<float>& sample) override {
        if (sample.size() != getSize()) {
            std::cout << "HumanWareNodeVector: incorrect sample size" << std::endl;
            return;
        }

        int i = 0;
        for (const auto& [child_name, child] : children) {
            
            int keys_for_cur_child = child->getSize();
            auto begin = sample.begin() + i;
            auto end = begin + keys_for_cur_child;
            i += keys_for_cur_child;

            std::vector<float> sub_sample(begin, end);
            
            child->processSample(sub_sample);
            
        }
    }

    const std::vector<std::string> generateDecoderKey() const override {
        std::vector<std::string> decoder_key;

        for (const auto& [child_name, child] : children) {
            const auto child_decoder_key = child->generateDecoderKey();

            for (const auto& path : child_decoder_key)
                decoder_key.push_back(child->getName() + "/" + path);
        }

        return decoder_key;
    }

    const float getValue(const std::string& key) const override { return -1; }
    const juce::NamedValueSet& getState() const override { 
        static const juce::NamedValueSet empty_state;
        return empty_state; 
    }

private:
    std::vector<std::pair<std::string, std::shared_ptr<WareNode>>> children;
};

// node factory to automate construction of HumanWareNodeVector
template <typename T>
std::function<std::shared_ptr<WareNode>()> makeNodeFactory() {
    return []() {
        return std::make_shared<T>();
    };
}

class HumanWareNodeVector : public WareNode {
public:
    HumanWareNodeVector(const std::string& name,
                        int num_children,
                        std::function<std::shared_ptr<WareNode>()> nodeFactory)
        : WareNode(name), num_children(num_children)
    {
        for (int i = 0; i < num_children; ++i) {
            auto child = nodeFactory();
            children.push_back(child);
        }
        
        keys_per_child = children[0]->getSize();
    }

    std::shared_ptr<WareNode> getChild(const std::string& name) const override {
        try {
            int index = std::stoi(name);
            jassert(index >= 0 && index < num_children);
            return children.at(index);
        } catch (const std::exception&) {
            jassertfalse; // String is not convertible to integer
            return nullptr;
        }
    }

    const int getSize() const override {
        return num_children * keys_per_child;
    }

    void processSample(const std::vector<float>& sample) override {
        if (sample.size() != getSize()) {
            std::cout << "HumanWareNodeVector: incorrect sample size" << std::endl;
            return;
        }
        
        for (int i = 0; i < num_children; ++i) {
            auto begin = sample.begin() + i * keys_per_child;
            auto end = begin + keys_per_child;
            std::vector<float> sub_sample(begin, end);

            children[i]->processSample(sub_sample);
        }
    }

    const std::vector<std::string> generateDecoderKey() const override {
        std::vector<std::string> decoder_key;

        // capture keys as decoder
        for (int i = 0; i < num_children; ++i) {
            auto child_decoder_key = children[i]->generateDecoderKey();

            for (const auto& path : child_decoder_key)
                decoder_key.push_back(std::to_string(i) + "/" + children[i]->getName() + "/" + path);
        }

            // concatenate decoder keys
            // decoder_key.insert(decoder_key.end(),child_decoder_key.begin(),child_decoder_key.end())
        return decoder_key;
    }

    const float getValue(const std::string& key) const override { return -1; }

protected:
    int num_children;
private:
    std::vector<std::shared_ptr<WareNode>> children;
    int keys_per_child;
};

// === TIER 2: concrete HumanWare classes ===

class FingerVector : public HumanWareNodeVector {
public:
    static constexpr const char* typeName = "fv";
    FingerVector(int size) : HumanWareNodeVector(typeName,size, makeNodeFactory<FlexSensor>()) {};
};

class Hand : public HumanWareNode {
public:
    static constexpr const char* typeName = "hand";
    Hand() : HumanWareNode(typeName) {
        addChild("gyro", std::make_shared<Gyroscope>());
        addChild("accel", std::make_shared<Accelerometer>());
        // addChild("fv", std::make_shared<FingerVector>(2));
    }
};

// === TIER 3: top-level HumanWare classes ===

class Body : public HumanWareNode {
public:
    static constexpr const char* typeName = "body";
    Body() : HumanWareNode(typeName) {
        addChild("hand", std::make_shared<Hand>());
        // addChild("flex", std::make_shared<FlexSensor>());
    };
};