add_library(core game_object.cpp engine.cpp)
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR}/include)