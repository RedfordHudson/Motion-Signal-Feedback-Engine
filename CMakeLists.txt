cmake_minimum_required(VERSION 4.0)
project(AudioPluginStarter)

set(CMAKE_CXX_STANDARD 23)

set(LIB_DR ${CMAKE_CURRENT_SOURCE_DIR}/libs)
# get CPM (only necessary for getting JUCE and other packages)
#[[
include(cmake/cpm.cmake)
#]]

# get JUCE
#[[
set(JUCE_VERSION 8.0.7)
CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG ${JUCE_VERSION}
    VERSIOn ${JUCE_VERSION}
    SOURCE_DIR ${LIB_DR}/juce
)

# problem: takes SUPER long
# solution: downloaded manually (git clone https://github.com/juce-framework/JUCE)

#]]

# treat warnings as errors
# set highest warning level (generate all possible warnings)
if (MSVC) # if compiler = Microsoft
    # add_compile_options(/Wall /WX)
    add_compile_options(/W4)
endif()

# loop in plugin

add_subdirectory(${LIB_DR}/juce)

add_subdirectory(plugin)