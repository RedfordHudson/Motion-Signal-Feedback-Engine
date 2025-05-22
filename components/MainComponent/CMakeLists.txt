# Create a static library for the MainComponent
add_library(MainComponent STATIC
    MainComponent.cpp
)

# Make the component's include directory public so other targets can include its headers
target_include_directories(MainComponent
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    # PRIVATE
    #     ${CMAKE_SOURCE_DIR}/libs/serialMonitor  # Add SerialMonitor include directory
)

# Link against required libraries
# PUBLIC means these dependencies will be propagated to any target that links against MainComponent
# JuceInterface provides all JUCE-related functionality (definitions, flags, etc.)
target_link_libraries(MainComponent
    PUBLIC
        # SerialMonitor
        JuceInterface
)

# Setup JUCE for this target
# This function call links against JuceInterface, which provides all necessary JUCE functionality
# The target will automatically get all JUCE definitions and recommended flags
setup_juce_target(MainComponent)
