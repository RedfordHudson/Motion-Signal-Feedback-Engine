cmake_minimum_required(VERSION 4.0)
project(AudioPluginStarter)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(JUCE)

add_subdirectory(TestApp)


# treat warnings as errors
# set highest warning level (generate all possible warnings)
# if (MSVC) # if compiler = Microsoft
#     # add_compile_options(/Wall /WX)
#     add_compile_options(/W4)
# endif()

