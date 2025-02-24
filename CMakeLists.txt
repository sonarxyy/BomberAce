cmake_minimum_required(VERSION 3.10)

project("ShapeDominance")

add_executable("ShapeDominance" main.cpp)

add_subdirectory(src/core)
add_subdirectory(src/graphics)
add_subdirectory(src/audio)

target_link_directories("ShapeDominance" PRIVATE lib)
target_link_libraries("ShapeDominance" PRIVATE core graphics audio SDL2 SDL2main SDL2_image SDL2_mixer SDL2_ttf)
target_include_directories("ShapeDominance" PRIVATE include)

# Copy assets folder
add_custom_command(TARGET ShapeDominance
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/Debug/assets)

# Copy DLLs
add_custom_command(TARGET ShapeDominance
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/lib/SDL2.dll ${CMAKE_SOURCE_DIR}/lib/SDL2_image.dll ${CMAKE_SOURCE_DIR}/lib/SDL2_mixer.dll ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf.dll
    ${CMAKE_BINARY_DIR}/Debug)


    


