add_library(SerialMonitor)
target_sources(SerialMonitor
    PUBLIC
        SerialPortHandler.h
    PRIVATE
        SerialPortHandler.cpp
)

# Set include directories
target_include_directories(SerialMonitor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link against JUCE core module and setup JUCE
target_link_libraries(SerialMonitor
    PUBLIC
        juce::juce_core
)

# Setup JUCE for this target with minimal modules
target_compile_definitions(SerialMonitor
    PRIVATE
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_REPORT_APP_USAGE=0
        JUCE_USE_XCURSOR=0
        JUCE_USE_XINERAMA=0
        JUCE_USE_XRANDR=0
        JUCE_USE_XSHM=0
        JUCE_USE_WEBKIT=0
        JUCE_USE_CURL=0
        JUCE_USE_MP3AUDIOFORMAT=0
        JUCE_USE_OGGVORBIS=0
        JUCE_USE_FLAC=0
        JUCE_USE_LAME_AUDIO_FORMAT=0
        JUCE_USE_WINDOWS_MEDIA_FORMAT=0
)

# Setup JUCE for this target
setup_juce_target(SerialMonitor)