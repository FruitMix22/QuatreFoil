cmake_minimum_required(VERSION 3.15)
project(GDP)


# OOOKAAAAAAAAAAY :
# KEEP THIS NEAT.
# ADD FILES AS NECCESSARY.
# GET USED TO IT BEING CONFUSING.
# EXPECT IT TO BREAK EVERY OTHER DAY.   


# Dependencies
add_subdirectory(externals/glfw)

# Neccessary for filesystem???
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Glad stuff
set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include)
set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/src/glad.c)
add_library(glad STATIC ${GLAD_SOURCE})
target_include_directories(glad PUBLIC ${GLAD_INCLUDE_DIR})

find_package(OpenGL REQUIRED)

# ENTT
#TODO -> Do this with glad and GLFW
include(FetchContent)
FetchContent_Declare(entt 
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.12.2
)
FetchContent_MakeAvailable(entt)

#-----------------------*
# SINGLE ENGINE LIBRARY
#-----------------------*
add_library(Engine STATIC
    # Core
    Engine/Core/include/EngineCore.hpp
    Engine/Core/src/EngineCore.cpp
    
    # Buffers
    Engine/Buffers/include/VBO.hpp
    Engine/Buffers/include/VAO.hpp
    Engine/Buffers/src/VBO.cpp
    Engine/Buffers/src/VAO.cpp
    
    # Renderer
    Engine/Renderer/include/Renderer.hpp
    Engine/Renderer/src/Renderer.cpp
    
    # Components
    Engine/Components/include/Renderable.hpp
    Engine/Components/src/Renderable.cpp
)

# Public includes
target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine
    ${GLAD_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/include
    $<TARGET_PROPERTY:EnTT::EnTT,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(Engine PRIVATE
    OpenGL::GL
    glfw
    glad
    EnTT::EnTT
)

#--------------------------------*
# Solution Explorer Organization 
#--------------------------------*
# Core 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Core/include PREFIX "Engine/Core/include" FILES
    Engine/Core/include/EngineCore.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Core/src PREFIX "Engine/Core/src" FILES
    Engine/Core/src/EngineCore.cpp
)

# Buffers 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Buffers/include PREFIX "Engine/Buffers/include" FILES
    Engine/Buffers/include/VBO.hpp
    Engine/Buffers/include/VAO.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Buffers/src PREFIX "Engine/Buffers/src" FILES
    Engine/Buffers/src/VBO.cpp
    Engine/Buffers/src/VAO.cpp
)

# Renderer 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/include PREFIX "Engine/Renderer/include" FILES
    Engine/Renderer/include/Renderer.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/src PREFIX "Engine/Renderer/src" FILES
    Engine/Renderer/src/Renderer.cpp
)

# Components - 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Components/include PREFIX "Engine/Components/include" FILES
    Engine/Components/include/Renderable.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Components/src PREFIX "Engine/Components/src" FILES
    Engine/Components/src/Renderable.cpp
)

#--------------*
# Game Project
#--------------*
add_executable(QuatreFoil
    QuatreFoil/src/main.cpp
)

target_link_libraries(QuatreFoil PRIVATE Engine)

# force solution ezplorer to see shader folder
file(GLOB QUATREFOIL_SHADERS "QuatreFoil/Assets/Shaders/*.glsl")
source_group("Assets\\Shaders" FILES ${QUATREFOIL_SHADERS})

foreach(shader ${QUATREFOIL_SHADERS})
    get_filename_component(shader_name ${shader} NAME)
    configure_file(${shader} ${CMAKE_CURRENT_BINARY_DIR}/Assets/shaders/${shader_name} COPYONLY)
endforeach()

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT QuatreFoil)