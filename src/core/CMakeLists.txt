add_library(core engine.cpp game_states_manager.cpp game_object.cpp main_menu.cpp options_menu.cpp in_game.cpp)
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)