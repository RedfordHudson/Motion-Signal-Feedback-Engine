add_executable(PureTest
    main.cpp
)

target_link_libraries(PureTest
    PRIVATE
        ${JUCE_MODULES}
        # juce::juce_gui_extra
        # HumanWare
        HumanWare
)