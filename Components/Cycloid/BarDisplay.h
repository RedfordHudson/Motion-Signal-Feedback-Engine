#include "DynamicCycloid.h"

class BarDisplay : public DynamicCycloid {
public:
    BarDisplay(const bool master)
        : DynamicCycloid("hypo",.25f,master)
    {}
};