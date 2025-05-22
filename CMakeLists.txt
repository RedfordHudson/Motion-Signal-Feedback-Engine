cmake_minimum_required(VERSION 3.15)
project(Synth-Engine VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Initialize JUCE
include(FetchContent)
set(JUCE_DIR "${CMAKE_SOURCE_DIR}/libs/juce" CACHE PATH "Path to JUCE")
add_subdirectory(${JUCE_DIR} JUCE_BUILD)

# Include JUCE settings
include(cmake/JuceSettings.cmake)

# Create the main application
juce_add_gui_app(Synth-Engine
    PRODUCT_NAME "Synth Engine"
    COMPANY_NAME "YourCompany"
    VERSION "1.0.0"
    BUNDLE_ID "com.yourcompany.synthengine"
    MICROPHONE_PERMISSION_ENABLED TRUE
)

# Add source files
target_sources(Synth-Engine
    PRIVATE
        app/source/Main.cpp
)

# Link against JUCE modules
target_link_libraries(Synth-Engine
    PRIVATE
        juce::juce_core
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_utils
        juce::juce_gui_basics
)

# Setup JUCE for this target
setup_juce_target(Synth-Engine)