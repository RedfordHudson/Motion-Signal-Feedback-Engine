cmake_minimum_required(VERSION 4.0)

project(AudioPlugin VERSION 0.1.0)

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

target_sources(${PROJECT_NAME}
    PRIVATE
        source/PluginEditor.cpp
        source/PluginProcessor.cpp
)
target_include_directories(${PROJECT_NAME}
    PRIVATE
        include
)

# solve warnings using setup recommended by JUCE
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        SerialMonitor
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

if (MSVC)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
        _CRT_SECURE_NO_WARNINGS
)
endif()