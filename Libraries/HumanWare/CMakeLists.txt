add_library(HumanWare
    HumanWare.cpp
    HumanWare.h
)

target_include_directories(HumanWare
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(HumanWare
    PRIVATE
        JUCEInterface
)
