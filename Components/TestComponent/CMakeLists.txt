add_library(TestComponent
    TestComponent.cpp
    TestComponent.h
)
target_include_directories(TestComponent
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(TestComponent
    PRIVATE
        JUCEInterface
)