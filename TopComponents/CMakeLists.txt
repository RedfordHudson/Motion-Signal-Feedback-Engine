message("Building ENTRY_POINT: ${ENTRY_POINT}")
add_juce_library(TopComponents ${ENTRY_POINT})
add_subdirectory(${ENTRY_POINT})