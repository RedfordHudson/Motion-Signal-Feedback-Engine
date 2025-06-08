#include "DynamicCycloid.h"

class BeatDisplay : public DynamicCycloid {
public:
    BeatDisplay(const float ratio)
        : DynamicCycloid("hypo",ratio)
    {}
};