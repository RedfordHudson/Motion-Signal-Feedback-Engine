add_library(HumanWare
    SensorWare.h
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

add_library(HumanWareTests
    HumanWareTests.h
)

target_include_directories(HumanWareTests
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(HumanWareTests
    PRIVATE
        JUCEInterface
    PUBLIC
        HumanWare
)
