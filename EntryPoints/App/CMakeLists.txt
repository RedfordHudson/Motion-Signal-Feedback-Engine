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

target_compile_definitions(${PROJECT_NAME} PUBLIC
    $<$<STREQUAL:${COMPONENT_MODE},GRAPHICS>:TEST_GRAPHICS>
    $<$<STREQUAL:${COMPONENT_MODE},AUDIO>:TEST_AUDIO>
    $<$<STREQUAL:${COMPONENT_MODE},MAIN>:BUILD_MAIN>
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${JUCE_MODULES}
        ${ENTRY_POINT}
)

get_target_property(dirs ${PROJECT_NAME} INCLUDE_DIRECTORIES)
message(STATUS "Direct include dirs: ${dirs}")
