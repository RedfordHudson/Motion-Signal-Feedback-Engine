add_library(Transport
    Transport.cpp
    Transport.h
)

target_include_directories(Transport
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Libraries/Transport
)

target_link_libraries(Transport
    PRIVATE
        JUCEInterface
)
