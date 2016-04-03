add_library (genetics_world gw_creature_tracker.cpp)
add_executable (run_world main.cpp)
target_link_libraries (run_world genetics_world)
