# set(COMPONENTS AudioTestComponent GraphVector Grapher)
set(COMPONENTS TestComponent)

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


foreach(COMP ${COMPONENTS})
    add_juce_library(${COMP})
endforeach()


# Force serial PDB writes
if(MSVC)
    add_compile_options(/FS)
endif()

add_subdirectory(TestComponent)
