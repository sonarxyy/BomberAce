cmake_minimum_required(VERSION 3.10)

project("ShapeDominance")

add_executable("ShapeDominance") # TODO: the main executable for the game

add_subdirectory(src/core)

target_link_directories("ShapeDominance" PRIVATE lib)
target_link_libraries("ShapeDominance" PRIVATE engine SDL2 SDL2main)
target_include_directories("Shape_Dominance" PRIVATE include)

