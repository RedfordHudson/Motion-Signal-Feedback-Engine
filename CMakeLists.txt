cmake_minimum_required(VERSION 4.0)
project(SynthEngine
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional, prefer standard C++

set(JUCE_MODULES_ONLY OFF CACHE BOOL "" FORCE)

add_subdirectory(JUCE)

# JUCEInterface
set(JUCE_MODULES
    juce::juce_audio_utils
    # juce::juce_gui_extra # if omitted, will cause linker error
    juce_core
    # juce_audio_basics
    # juce_audio_devices
    # juce_audio_utils
    # juce_audio_formats
    # juce_gui_basics
    # juce_gui_extra
    juce_dsp
)

add_library(JUCE_USAGE_REQUIREMENTS INTERFACE)
target_link_libraries(JUCE_USAGE_REQUIREMENTS
    INTERFACE
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
target_include_directories(JUCE_USAGE_REQUIREMENTS INTERFACE ${CMAKE_SOURCE_DIR}/JUCE/modules)
target_compile_definitions(JUCE_USAGE_REQUIREMENTS INTERFACE
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_MODULE_AVAILABLE_juce_core=1
)

add_subdirectory(Libraries)
add_subdirectory(Components)

add_subdirectory(App)
add_subdirectory(PureTest)

# Force serial PDB writes
# if(MSVC)
#     add_compile_options(/FS)
# endif()