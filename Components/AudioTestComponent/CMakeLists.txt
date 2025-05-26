add_library(AudioTestComponent
    AudioTestComponent.cpp
    AudioTestComponent.h
)
target_include_directories(AudioTestComponent
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(AudioTestComponent
    PRIVATE
        JUCEInterface

        Transport
        Cycle
        OscillatorWrapper
        
        Grapher
)