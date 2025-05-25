# JUCE wrapper of add_executable
juce_add_gui_app(${PROJECT_NAME}
    MODULES
    ${JUCE_MODULES}
)

# MUST BE LINKED OUTSIDE OF juce_add_gui_app OR ELSE WILL CAUSE LINKER ISSUE
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

juce_generate_juce_header(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    # explicitly links those modules into the final executable
    # necessary b/c they have external dependencies
        juce::juce_audio_utils
        juce::juce_gui_extra # if omitted, will cause linker error
        # TestComponent
        AudioTestComponent
        PUBLIC
        # juce::juce_recommended_config_flags
        # juce::juce_recommended_lto_flags
        # juce::juce_recommended_warning_flags
)