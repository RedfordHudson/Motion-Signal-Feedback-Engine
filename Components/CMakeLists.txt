set(COMPONENTS GraphVector Grapher)

foreach(COMP ${COMPONENTS})
    add_juce_library(Components ${COMP})
endforeach()

foreach(COMP ${COMPONENTS})
    add_subdirectory(${COMP})
endforeach()

add_subdirectory(Cycloid)