set(LIBS Transport OscillatorWrapper Cycle SerialMonitor)
# HumanWare is added separately (bottom) b/c it has different architecture

foreach(LIB ${LIBS})
    add_juce_library(Libraries ${LIB})
endforeach()

foreach(LIB ${LIBS})
    add_subdirectory(${LIB})
endforeach()

add_subdirectory(HumanWare)
