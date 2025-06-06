# add_library(HumanWare
#     SensorWare.h
#     HumanWare.h
# )

# target_include_directories(HumanWare
#     PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# target_link_libraries(HumanWare
#     PRIVATE
#         JUCEInterface
# )

add_library(HumanWareTests INTERFACE
    # HumanWareTests.h
    # HumanWareTests.cpp
)

# necessary when you dont use .cpp file
# set_target_properties(HumanWareTests PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(HumanWareTests
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(HumanWareTests
    INTERFACE
        JUCE_USAGE_REQUIREMENTS
    # PUBLIC
    #     HumanWare
)
