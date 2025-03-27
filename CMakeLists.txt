cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17) # Compatible with constexpr.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("BomberAce")

add_executable("BomberAce" WIN32 ${CMAKE_SOURCE_DIR}/src/main.cpp bomber_ace.rc)

add_subdirectory(src/core)
add_subdirectory(src/graphics)
add_subdirectory(src/audio)

target_link_directories("BomberAce" PRIVATE lib)
target_link_libraries("BomberAce" PRIVATE core graphics audio SDL2main SDL2 SDL2_image SDL2_mixer SDL2_ttf)
target_include_directories("BomberAce" PRIVATE include)

# Allow whitespace in name.
set_target_properties(BomberAce PROPERTIES OUTPUT_NAME "Bomber Ace")

# Copy assets folder.
add_custom_command(TARGET "BomberAce"
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets)

# Copy DLLs.
add_custom_command(TARGET "BomberAce"
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/lib/SDL2.dll ${CMAKE_SOURCE_DIR}/lib/SDL2_image.dll ${CMAKE_SOURCE_DIR}/lib/SDL2_mixer.dll ${CMAKE_SOURCE_DIR}/lib/SDL2_ttf.dll
    ${CMAKE_BINARY_DIR})
