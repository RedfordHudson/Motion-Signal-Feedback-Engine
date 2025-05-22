# Initialize JUCE
include(FetchContent)

# Use local JUCE repository
set(JUCE_DIR "${CMAKE_SOURCE_DIR}/libs/juce" CACHE PATH "Path to JUCE")

# Set JUCE options before including it
set(JUCE_BUILD_EXAMPLES OFF CACHE BOOL "Build JUCE examples" FORCE)
set(JUCE_BUILD_EXTRAS OFF CACHE BOOL "Build JUCE extras" FORCE)
set(JUCE_ENABLE_MODULE_SOURCE_GROUPS ON CACHE BOOL "Enable module source groups" FORCE)

# Platform-specific settings
if(WIN32)
    set(JUCE_DISPLAY_SPLASH_SCREEN 0)
    set(JUCE_REPORT_APP_USAGE 0)
    set(JUCE_USE_XCURSOR 0)
    set(JUCE_USE_XINERAMA 0)
    set(JUCE_USE_XRANDR 0)
    set(JUCE_USE_XSHM 0)
    set(JUCE_USE_WEBKIT 0)
    set(JUCE_USE_CURL 0)
    set(JUCE_USE_MP3AUDIOFORMAT 0)
    set(JUCE_USE_OGGVORBIS 0)
    set(JUCE_USE_FLAC 0)
    set(JUCE_USE_MP3AUDIOFORMAT 0)
    set(JUCE_USE_LAME_AUDIO_FORMAT 0)
    set(JUCE_USE_WINDOWS_MEDIA_FORMAT 0)
endif()

# Add JUCE as a subdirectory
add_subdirectory(${JUCE_DIR} JUCE_BUILD)

# Common JUCE module configuration
set(JUCE_MODULES
    juce_core
    juce_audio_basics
    juce_audio_devices
    juce_audio_utils
    juce_audio_formats
    juce_gui_basics
    juce_gui_extra
    juce_dsp
)

# Common JUCE definitions
set(JUCE_DEFINITIONS
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

# Function to setup JUCE for a target
function(setup_juce_target TARGET_NAME)
    target_compile_definitions(${TARGET_NAME}
        PRIVATE
            ${JUCE_DEFINITIONS}
    )
    
    target_link_libraries(${TARGET_NAME}
        PRIVATE
            juce::juce_recommended_config_flags
            juce::juce_recommended_lto_flags
            juce::juce_recommended_warning_flags
    )
    
    foreach(MODULE ${JUCE_MODULES})
        target_link_libraries(${TARGET_NAME} PRIVATE juce::${MODULE})
    endforeach()
endfunction() 