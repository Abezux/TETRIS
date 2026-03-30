cmake_minimum_required(VERSION 3.14)
project(Tetris VERSION 2.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Includes
include_directories(include vendor/raylib/include)

# Source files
file(GLOB SRCS "src/*.cpp")
list(APPEND SRCS main.cpp)

# Target executable
add_executable(Tetris ${SRCS})

# Target link directories and libraries
target_link_directories(Tetris PRIVATE vendor/raylib/lib)
target_link_libraries(Tetris PRIVATE raylib GL m pthread dl rt X11)

# Platform specific settings
if(WIN32)
    target_link_libraries(Tetris PRIVATE winmm gdi32)
endif()
