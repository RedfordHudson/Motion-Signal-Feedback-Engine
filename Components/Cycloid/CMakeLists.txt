# INTERFACE b/c only .h files
add_library(FrequencyDisplay INTERFACE)

target_include_directories(FrequencyDisplay
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(FrequencyDisplay
    INTERFACE
        JUCE_USAGE_REQUIREMENTS
)