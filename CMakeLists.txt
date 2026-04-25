

cmake_minimum_required(VERSION 3.10)
project(ppca_5b)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable for the cheat program
add_executable(cheat cheat.cpp)

# Add executable for the anticheat program
add_executable(anticheat anticheat.cpp)

# Create a symbolic link for the code executable
add_custom_command(
    TARGET cheat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    $<TARGET_FILE:cheat> ${CMAKE_BINARY_DIR}/code
)

add_custom_command(
    TARGET anticheat POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    $<TARGET_FILE:anticheat> ${CMAKE_BINARY_DIR}/code
)

