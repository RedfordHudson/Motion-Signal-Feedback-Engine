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
        ${JUCE_MODULES}
        AudioTestComponent
)