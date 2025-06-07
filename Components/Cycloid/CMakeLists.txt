# INTERFACE b/c only .h files
add_library(CycloidDisplays INTERFACE)

target_include_directories(CycloidDisplays
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(CycloidDisplays
    INTERFACE
        JUCE_USAGE_REQUIREMENTS
)