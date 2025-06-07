
# usage requirements

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

# add static lib wrapper macro

function(add_juce_library DIR TARGET_NAME)

    set(SUB_DIR ${DIR}/${TARGET_NAME})

    add_library(${TARGET_NAME}
        ${CMAKE_SOURCE_DIR}/${SUB_DIR}/${TARGET_NAME}.cpp
        ${CMAKE_SOURCE_DIR}/${SUB_DIR}/${TARGET_NAME}.h
    )

    target_include_directories(${TARGET_NAME}
        PUBLIC
            ${CMAKE_SOURCE_DIR}/${SUB_DIR}
    )

    target_link_libraries(${TARGET_NAME}
        PRIVATE
            JUCE_USAGE_REQUIREMENTS
    )
endfunction()
