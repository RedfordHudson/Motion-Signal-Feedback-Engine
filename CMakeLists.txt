cmake_minimum_required(VERSION 4.0)
project(SynthEngine
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # optional but recommended for portability


add_subdirectory(JUCE)

add_library(JUCECoreModules STATIC)

# target_sources(JUCECoreModules PRIVATE
#     # JUCE/modules/juce_core/juce_core.cpp
#     # JUCE/modules/juce_data_structures/juce_data_structures.cpp
#     # JUCE/modules/juce_events/juce_events.cpp
#     # JUCE/modules/juce_graphics/juce_graphics.cpp
#     JUCE/modules/juce_gui_basics/juce_gui_basics.cpp
#     JUCE/modules/juce_gui_extra/juce_gui_extra.cpp
# )

target_link_libraries(JUCECoreModules PRIVATE
    juce::juce_gui_extra
    juce::juce_gui_basics
)

target_include_directories(JUCECoreModules PUBLIC
    JUCE/modules
)

target_compile_definitions(JUCECoreModules   PUBLIC
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
)

# target_compile_definitions(JUCECoreModules PUBLIC
#     # JUCE_MODULE_AVAILABLE_juce_core=1
#     # JUCE_MODULE_AVAILABLE_juce_data_structures=1
#     # JUCE_MODULE_AVAILABLE_juce_events=1
#     # JUCE_MODULE_AVAILABLE_juce_graphics=1
#     JUCE_MODULE_AVAILABLE_juce_gui_basics=1
#     JUCE_MODULE_AVAILABLE_juce_gui_extra=1
# )

add_subdirectory(Components)
add_subdirectory(App)

