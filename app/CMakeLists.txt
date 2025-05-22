cmake_minimum_required(VERSION 4.0)

# Create the main application target using JUCE's helper function
# This sets up the basic application structure with the specified name and version
juce_add_gui_app(${PROJECT_NAME}
    TARGET_PREFIX ""  # Optional, removes prefix from target name
    PRODUCT_NAME "MotionSynth"
    VERSION 1.0.0
)

# Generate JUCE header with project information
# This creates a header file with project name, version, etc.
juce_generate_juce_header(${PROJECT_NAME})

# Add source files to the application
target_sources(${PROJECT_NAME}
    PRIVATE
        Main.cpp
)

# Add include directories for finding component headers
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/components
)

# Link against required libraries
# PRIVATE means these dependencies are only used by this target and not propagated
# JuceInterface provides all JUCE-related functionality (definitions, flags, etc.)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        MainComponent
        JuceInterface
)

# Setup JUCE for this target
# This function call links against JuceInterface, which provides all necessary JUCE functionality
# The target will automatically get all JUCE definitions and recommended flags
setup_juce_target(${PROJECT_NAME})

# Set C++ standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)

# MSVC-specific settings
if (MSVC)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
            _CRT_SECURE_NO_WARNINGS
    )
endif()