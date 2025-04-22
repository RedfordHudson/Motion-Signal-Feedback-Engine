cmake_minimum_required(VERSION 4.0)

project(AudioPlugin VERSION 0.1.0)

#[[
juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME Redford
    IS_SYNTH TRUE # disables audio input channels
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    PLUGIN_MANUFACTURER_CODE JUCE
    PLUGIN_CODE AUPL
    FORMATS Standalone # hosts locally instead of via DAW
    PRODUCT_NAME "YourPluginName"
)
#]]

# analogue of add_executable?
juce_add_gui_app(${PROJECT_NAME}
    TARGET_PREFIX ""  # Optional, removes prefix from target name
    PRODUCT_NAME "YourPluginName"
    VERSION 1.0.0
    MODULES
    # specify JUCE modules your application will need in the MODULES list 
    # ensures modules are compiled into project and made available during build process
        juce_audio_basics
        juce_audio_devices
        juce_audio_utils
        juce_audio_formats
        juce_gui_basics
        juce_gui_extra
        juce_dsp
    # Add other modules based on your needs
)


target_sources(${PROJECT_NAME}
    PRIVATE
        source/Main.cpp
        source/MainComponent.cpp
        source/SerialPortHandler.cpp
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    # explicitly links those modules into the final executable
    # necessary b/c they have external dependencies
        juce::juce_audio_utils
        juce::juce_gui_extra
        # SerialMonitor
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# solve warnings using setup recommended by JUCE
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if (MSVC)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
        _CRT_SECURE_NO_WARNINGS
)
endif()