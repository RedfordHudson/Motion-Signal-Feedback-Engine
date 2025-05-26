
# Grapher.h in TestComponent.h -> PUBLIC; must progagate to main app (top-level executable)
# Grapher.h in TestComponent.cpp -> PRIVATE; stays local to TestComponent
target_link_libraries(TestComponent
    PRIVATE
        HumanWare
        SerialMonitor
)