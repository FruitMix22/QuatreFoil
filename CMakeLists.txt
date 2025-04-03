cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(2DRenderer)

# Main Executable
add_executable(2DRenderer 2DRenderer/src/main.cpp)

# USE THIS AS STARTUP
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT 2DRenderer)

# GLFW
add_subdirectory(externals/glfw)

# Glad
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include)

add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/src/glad.c)
target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include)

# OpenGL
find_package(OpenGL REQUIRED)



# Link Libraries
target_link_libraries(2DRenderer
    OpenGL::GL
    glfw
    glad
)

# Maybe itll fix???
set(CMAKE_SUPPRESS_REGENERATION TRUE)

