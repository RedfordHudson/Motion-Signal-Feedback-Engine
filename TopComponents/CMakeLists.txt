message("Building TOP_COMPONENT: ${TOP_COMPONENT}")
add_juce_library(TopComponents ${TOP_COMPONENT})
add_subdirectory(${TOP_COMPONENT})