# INTERFACE b/c only .h files
add_library(Cycloid INTERFACE)

target_include_directories(Cycloid
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Cycloid
    INTERFACE
        JUCE_USAGE_REQUIREMENTS
)