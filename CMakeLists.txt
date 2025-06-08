cmake_minimum_required(VERSION 4.0)
project(SynthEngine
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional, prefer standard C++

# Suppress generator platform warning
unset(ENV{CMAKE_GENERATOR_PLATFORM})

set(JUCE_MODULES_ONLY OFF CACHE BOOL "" FORCE)

set(COMPONENT_MODE "AUDIO" CACHE STRING "Component to build: GRAPHICS, AUDIO, MAIN" FORCE)
set_property(CACHE COMPONENT_MODE PROPERTY STRINGS GRAPHICS AUDIO MAIN)
message("Configuring on mode: ${COMPONENT_MODE}")

if(COMPONENT_MODE STREQUAL "GRAPHICS")
    set(TOP_COMPONENT GraphicsTester)
elseif(COMPONENT_MODE STREQUAL "AUDIO")
    set(TOP_COMPONENT AudioTester)
elseif(COMPONENT_MODE STREQUAL "MAIN")
    set(TOP_COMPONENT MainComponent)
else()
    message(FATAL_ERROR "Unknown COMPONENT_MODE: ${COMPONENT_MODE}")
endif()

add_subdirectory(cmake_utils)

set(JUCE_MODULES
    juce::juce_audio_utils
    juce::juce_dsp
    # juce::juce_gui_basics
)

add_subdirectory(JUCE)

add_subdirectory(Libraries)
add_subdirectory(Components)

add_subdirectory(TopComponents)
add_subdirectory(EntryPoints)