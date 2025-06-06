add_executable(PureTest
    main.cpp
)

target_link_libraries(PureTest
    PRIVATE
        # juce::juce_core
        ${JUCE_MODULES}
        # juce::juce_gui_extra
        # HumanWare
        HumanWareTests
)