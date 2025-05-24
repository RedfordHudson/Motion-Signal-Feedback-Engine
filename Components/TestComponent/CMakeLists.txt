add_library(TestComponent
    TestComponent.cpp
    TestComponent.h
)
target_include_directories(TestComponent
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# MUST BE PUBLIC TO PROPAGATE TO MAIN APP (TOP-LEVEL EXECUTABLE)
target_link_libraries(TestComponent
    PUBLIC
        Grapher
    PRIVATE
        JUCEInterface
)