cmake_minimum_required(VERSION 4.0)
project(SynthEngine
    VERSION 0.1.0
    LANGUAGES CXX
)

add_subdirectory(JUCE)

# JUCEInterface
add_library(JUCEInterface INTERFACE)
set(JUCE_MODULES
    juce_core
    # juce_audio_basics
    # juce_audio_devices
    # juce_audio_utils
    # juce_audio_formats
    # juce_gui_basics
    # juce_gui_extra
    # juce_dsp
)
target_link_libraries(JUCEInterface INTERFACE ${JUCE_MODULES})

add_subdirectory(Libraries)
# add_subdirectory(Components)

# add_subdirectory(App)
add_subdirectory(PureTest)

