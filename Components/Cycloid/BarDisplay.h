#include "DynamicCycloid.h"

class BarDisplay : public DynamicCycloid {
public:
    BarDisplay()
        : DynamicCycloid("hypo",.25f)
    {}
};