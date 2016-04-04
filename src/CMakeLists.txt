add_library (genetics_world gw_behavior_factory.cpp gw_behavior_reproduction.cpp gw_creature_tracker.cpp gw_sense_energy.cpp gw_sense_factory.cpp)
add_executable (run_world main.cpp)
target_link_libraries (run_world genetics_world)
