add_library(Grapher
    Grapher.cpp
    Grapher.h
)
target_include_directories(Grapher
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

message("Grapher include dir: ${CMAKE_CURRENT_SOURCE_DIR}")
get_target_property(GRAPHER_INCLUDES Grapher INCLUDE_DIRECTORIES)
message("Includes for Grapher: ${GRAPHER_INCLUDES}")


target_link_libraries(Grapher
    PRIVATE
        JUCEInterface
)