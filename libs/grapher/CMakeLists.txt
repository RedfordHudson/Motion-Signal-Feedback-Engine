add_library(Grapher)
target_sources(Grapher
    PUBLIC
        grapher.h
    PRIVATE
        grapher.cpp
)
target_include_directories(Grapher PUBLIC ${CMAKE_CURRENT_LIST_DIR})