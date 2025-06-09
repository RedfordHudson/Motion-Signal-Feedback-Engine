#include "DynamicCycloid.h"

class BarDisplay : public DynamicCycloid {
public:
    BarDisplay(const std::string& name, const bool master)
        : DynamicCycloid(name,"hypo",.25f,master)
    {}
};