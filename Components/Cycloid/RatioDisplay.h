#include "StaticCycloid.h"

class RatioDisplay : public StaticCycloid {
public:
    RatioDisplay()
        : StaticCycloid("epi",1.0f/3.0f)
    {}
};