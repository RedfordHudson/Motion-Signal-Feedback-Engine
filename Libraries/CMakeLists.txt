# add_subdirectory(SerialSimulator)
# add_subdirectory(HumanWare)

set(LIBS Transport OscillatorWrapper Cycle)

function(add_juce_library TARGET_NAME)

    add_library(${TARGET_NAME}
        ${TARGET_NAME}/${TARGET_NAME}.cpp
        ${TARGET_NAME}/${TARGET_NAME}.h
    )

    target_include_directories(${TARGET_NAME}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}
    )

    target_link_libraries(${TARGET_NAME}
        PRIVATE
            JUCEInterface
    )
endfunction()


foreach(LIB ${LIBS})
    # add_subdirectory(${LIB})
    add_juce_library(${LIB})

endforeach()
