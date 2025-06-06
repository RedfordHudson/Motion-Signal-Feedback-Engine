# INTERFACE b/c only .h files
add_library(HumanWare INTERFACE)

target_include_directories(HumanWare
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(HumanWare
    INTERFACE
        JUCE_USAGE_REQUIREMENTS
)