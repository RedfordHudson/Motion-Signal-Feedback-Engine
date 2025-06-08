#include "DynamicCycloid.h"

class BeatDisplay : public DynamicCycloid {
public:
    BeatDisplay(const float ratio, const bool master)
        : DynamicCycloid("hypo",ratio,master)
    {}
};