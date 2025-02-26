add_library(graphics text_manager.cpp texture_manager.cpp main_menu.cpp)
target_include_directories(graphics PUBLIC ${CMAKE_SOURCE_DIR}/include)