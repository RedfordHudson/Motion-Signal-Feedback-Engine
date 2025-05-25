add_library(TestComponent
    TestComponent.cpp
    TestComponent.h
)
target_include_directories(TestComponent
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Grapher.h in TestComponent.h -> PUBLIC; must progagate to main app (top-level executable)
# Grapher.h in TestComponent.cpp -> PRIVATE; stays local to TestComponent
target_link_libraries(TestComponent
    PUBLIC
        # Grapher
    PRIVATE
        JUCEInterface
        Grapher
        HumanWare
        SerialSimulator
)