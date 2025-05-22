# Common settings for all libraries
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library-specific settings
set(SERIAL_MONITOR_VERSION "1.0.0")
set(GRAPHER_VERSION "1.0.0")

# Add internal libraries
# add_subdirectory(serialMonitor)
# add_subdirectory(grapher)

# Export library targets
set(LIBRARY_TARGETS
    SerialMonitor
    Grapher
    CACHE INTERNAL "List of library targets"
) 