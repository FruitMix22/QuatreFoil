cmake_minimum_required(VERSION 3.10)
project(Game-Development-Project)

set(CMAKE_CXX_STANDARD 17)

# GLFW
add_subdirectory(externals/glfw)

# Glad
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include)

add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/src/glad.c)
target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include)

# OpenGL
find_package(OpenGL REQUIRED)

# Main Executable
add_executable(2DRenderer 2DRenderer/src/main.cpp)

# Link Libraries
target_link_libraries(2DRenderer
    OpenGL::GL
    glfw
    glad
)

# Maybe itll fix???
set(CMAKE_SUPPRESS_REGENERATION TRUE)

