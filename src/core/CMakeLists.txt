add_library(core engine.cpp game_states_manager.cpp game_object.cpp )
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)