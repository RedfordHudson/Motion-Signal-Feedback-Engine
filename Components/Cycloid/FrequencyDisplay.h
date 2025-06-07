#include "StaticCycloid.h"

class FrequencyDisplay : public StaticCycloid {
public:
    FrequencyDisplay()
        : StaticCycloid("epi",1.0f/3.0f)
    {}
};