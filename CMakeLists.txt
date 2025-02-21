cmake_minimum_required(VERSION 3.10)

project("ShapeDominance")

add_executable("ShapeDominance" main.cpp)
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/Debug/assets
    )
add_dependencies("ShapeDominance" copy_assets)

add_subdirectory(src/core)
add_subdirectory(src/graphics)

target_link_directories("ShapeDominance" PRIVATE lib)
target_link_libraries("ShapeDominance" PRIVATE core graphics SDL2 SDL2main SDL2_image)
target_include_directories("ShapeDominance" PRIVATE include)
