
# Grapher.h in TestComponent.h -> PUBLIC; must progagate to main app (top-level executable)
# Grapher.h in TestComponent.cpp -> PRIVATE; stays local to TestComponent
target_link_libraries(GraphicsTester
    PRIVATE
)

get_target_property(dirs GraphicsTester INCLUDE_DIRECTORIES)
message(STATUS "Direct include dirs: ${dirs}")
