#include "StaticCycloid.h"

class RatioDisplay : public StaticCycloid {
public:
    RatioDisplay(const std::string& name)
        : StaticCycloid(name,"epi",1.0f/3.0f)
    {}
};