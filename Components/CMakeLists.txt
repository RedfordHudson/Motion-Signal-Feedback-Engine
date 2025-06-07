# set(COMPONENTS GraphVector Grapher)
set(COMPONENTS Cycloid)

# foreach(COMP ${COMPONENTS})
#     add_juce_library(Components ${COMP})
# endforeach()

foreach(COMP ${COMPONENTS})
    add_subdirectory(${COMP})
endforeach()