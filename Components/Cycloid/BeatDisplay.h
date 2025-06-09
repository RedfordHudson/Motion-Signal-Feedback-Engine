#include "DynamicCycloid.h"

class BeatDisplay : public DynamicCycloid {
public:
    BeatDisplay(const std::string& name, const float ratio, const bool master)
        : DynamicCycloid(name,"hypo",ratio,master)
    {}
};