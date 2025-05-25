add_library(LibraryLib
    librarylib.h
)
target_include_directories(LibraryLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(LibraryLib
    PRIVATE
        JUCECoreModules
)