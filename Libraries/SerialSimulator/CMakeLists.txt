add_library(SerialSimulator
    SerialSimulator.cpp
    SerialSimulator.h
)

target_include_directories(SerialSimulator
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(SerialSimulator
    PRIVATE
        JUCEInterface
)
