cmake_minimum_required(VERSION 3.15)

#--------------------------
# Project configuration
#--------------------------
# Change PROJECT_NAME to your game's name.
# Change GAME_DIR to point to your game's source folder.
# Further down there is the game section, you will need to change/add anything relevant to your game.
# By default, I've set PROJECT_NAME to "ExampleGame" and GAME_DIR to "ExampleGame/"

set(PROJECT_NAME "ExampleGame")              # Change name to your project (executable name).
set(ENGINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine")   # Change if you have moved the engine folder.
set(GAME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ExampleGame")  # Folder name for your project.

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX) # Sets project name to name you established above.

#------------
# C++ 
#------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# (If you wish to change C++ version, change the 17 to which version you'd like).

#--------------------
# Dependencies
#--------------------

# --- GLFW ----
# GLFW should be in the already assigned folder. 
# If you move it , update the path below.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw)

# --- GLAD ---
# Again, it is already in the correct folder upon download.
# If moved, change it to match your current location.

set(GLAD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include)
set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/src/glad.c)
add_library(glad STATIC ${GLAD_SOURCE})
target_include_directories(glad PUBLIC ${GLAD_INCLUDE_DIR})

# --- OpenGL Core ---
find_package(OpenGL REQUIRED)


# --- EnTT ---
# EnTT is fetched from github automatically.
include(FetchContent)
FetchContent_Declare(entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.12.2
)
FetchContent_MakeAvailable(entt)


# --- ImGui ---
#Also fetches from GitHub.
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)
FetchContent_MakeAvailable(imgui)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/include
)

# Enable docking support for ImGui.
target_compile_definitions(imgui PUBLIC IMGUI_ENABLE_DOCKING)
#---------------------
# Engine Library
#---------------------
# This builds the engine as a static library. Other projects e.g., your game will link to it.
# IF adding new files to the game engine, add them here in their relevant section.

add_library(Engine STATIC
    # Core and sources
    ${ENGINE_DIR}/Core/include/EngineCore.hpp
   ${ENGINE_DIR}/Core/include/Layer.hpp
    ${ENGINE_DIR}/Core/include/Input.hpp
    ${ENGINE_DIR}/Core/include/Console.hpp

  ${ENGINE_DIR}/Core/src/EngineCore.cpp
     ${ENGINE_DIR}/Core/src/Input.cpp
    ${ENGINE_DIR}/Core/src/Console.cpp
    
    # Buffers
   ${ENGINE_DIR}/Buffers/include/VBO.hpp
    ${ENGINE_DIR}/Buffers/include/VAO.hpp
    ${ENGINE_DIR}/Buffers/include/EBO.hpp
    ${ENGINE_DIR}/Buffers/include/FBO.hpp

    ${ENGINE_DIR}/Buffers/src/VBO.cpp
    ${ENGINE_DIR}/Buffers/src/VAO.cpp
    ${ENGINE_DIR}/Buffers/src/EBO.cpp
    ${ENGINE_DIR}/Buffers/src/FBO.cpp
    
    # Renderer
    ${ENGINE_DIR}/Renderer/include/Renderer.hpp
    ${ENGINE_DIR}/Renderer/include/ImGuiLayer.hpp
    ${ENGINE_DIR}/Renderer/include/Shader.hpp
    ${ENGINE_DIR}/Renderer/include/Texture.hpp
    ${ENGINE_DIR}/Renderer/include/Camera.hpp
    ${ENGINE_DIR}/Renderer/src/Renderer.cpp
    ${ENGINE_DIR}/Renderer/src/ImGuiLayer.cpp
    ${ENGINE_DIR}/Renderer/src/Shader.cpp
    ${ENGINE_DIR}/Renderer/src/Texture.cpp
    ${ENGINE_DIR}/Renderer/src/Camera.cpp
    
    # Components
    ${ENGINE_DIR}/Components/Renderable.hpp
    ${ENGINE_DIR}/Components/Transform.hpp
    ${ENGINE_DIR}/Components/PlayerComp.hpp
    ${ENGINE_DIR}/Components/EnemyComp.hpp
    ${ENGINE_DIR}/Components/RenderLayer.hpp
    ${ENGINE_DIR}/Components/Collider.hpp
    ${ENGINE_DIR}/Components/HitBox.hpp
    ${ENGINE_DIR}/Components/Animator.hpp
)

# Public includes so your game can see the engine headers.
target_include_directories(Engine PUBLIC
    ${ENGINE_DIR}                           
    ${GLAD_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/include
    $<TARGET_PROPERTY:EnTT::EnTT,INTERFACE_INCLUDE_DIRECTORIES>
    ${imgui_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/stb
)

# Give engine dependencies.
target_link_libraries(Engine PRIVATE
    OpenGL::GL
    glfw
    glad
    EnTT::EnTT
    imgui
)

#-----------------------------------
# Solution Explorer Organization 
#-----------------------------------

#IF you add new files, this will help manage them in visual studios solution explorer.
# If you want to add a new folder, add it like this,
#   target_sources (Engine PRIVATE
#       ${ENGINE_DIR}/Audio/include/AudioEngine.hpp
#       ${ENGINE_DIR}/Audio/src/AudioEngine.cpp
#   )
#   Then add to include dirs:
#   target_include_directories(Engine PUBLIC ${ENGINE_DIR}/Audio/include)
#

# Core
source_group(TREE ${ENGINE_DIR}/Core/include   PREFIX "Engine/Core/include" FILES
    ${ENGINE_DIR}/Core/include/EngineCore.hpp
    ${ENGINE_DIR}/Core/include/Layer.hpp
    ${ENGINE_DIR}/Core/include/Input.hpp
    ${ENGINE_DIR}/Core/include/Console.hpp
)
source_group(TREE ${ENGINE_DIR}/Core/src       PREFIX "Engine/Core/src"     FILES
    ${ENGINE_DIR}/Core/src/EngineCore.cpp
    ${ENGINE_DIR}/Core/src/Input.cpp
    ${ENGINE_DIR}/Core/src/Console.cpp
)

# Buffers
source_group(TREE ${ENGINE_DIR}/Buffers/include PREFIX "Engine/Buffers/include" FILES
    ${ENGINE_DIR}/Buffers/include/VBO.hpp
    ${ENGINE_DIR}/Buffers/include/VAO.hpp
    ${ENGINE_DIR}/Buffers/include/EBO.hpp
    ${ENGINE_DIR}/Buffers/include/FBO.hpp
)
source_group(TREE ${ENGINE_DIR}/Buffers/src     PREFIX "Engine/Buffers/src"    FILES
    ${ENGINE_DIR}/Buffers/src/VBO.cpp
    ${ENGINE_DIR}/Buffers/src/VAO.cpp
    ${ENGINE_DIR}/Buffers/src/EBO.cpp
    ${ENGINE_DIR}/Buffers/src/FBO.cpp
)

# Renderer
source_group(TREE ${ENGINE_DIR}/Renderer/include PREFIX "Engine/Renderer/include" FILES
    ${ENGINE_DIR}/Renderer/include/Renderer.hpp
    ${ENGINE_DIR}/Renderer/include/ImGuiLayer.hpp
    ${ENGINE_DIR}/Renderer/include/Shader.hpp
    ${ENGINE_DIR}/Renderer/include/Texture.hpp
    ${ENGINE_DIR}/Renderer/include/Camera.hpp
)
source_group(TREE ${ENGINE_DIR}/Renderer/src     PREFIX "Engine/Renderer/src"    FILES
    ${ENGINE_DIR}/Renderer/src/Renderer.cpp
    ${ENGINE_DIR}/Renderer/src/ImGuiLayer.cpp
    ${ENGINE_DIR}/Renderer/src/Shader.cpp
    ${ENGINE_DIR}/Renderer/src/Texture.cpp
    ${ENGINE_DIR}/Renderer/src/Camera.cpp
)

# Components
source_group(TREE ${ENGINE_DIR}/Components PREFIX "Engine/Components" FILES
    ${ENGINE_DIR}/Components/Renderable.hpp
    ${ENGINE_DIR}/Components/Transform.hpp
    ${ENGINE_DIR}/Components/PlayerComp.hpp
    ${ENGINE_DIR}/Components/EnemyComp.hpp
    ${ENGINE_DIR}/Components/RenderLayer.hpp
    ${ENGINE_DIR}/Components/Collider.hpp
    ${ENGINE_DIR}/Components/HitBox.hpp
    ${ENGINE_DIR}/Components/Animator.hpp
    # ${ENGINE_DIR}/Components/Camera.hpp
)

#------------------------
# Game Project
#------------------------

#This is what builds and adds the game.
# Replace everything relevant with your game.


#  Gather headers & sources for ExampleGame
file(GLOB EXAMPLE_HEADERS "${GAME_DIR}/include/*.hpp")
set(EXAMPLE_SOURCES
    ${GAME_DIR}/src/ExampleGame.cpp
    ${GAME_DIR}/src/EntryPoint.cpp
)

# Create executable.
add_executable(${PROJECT_NAME}
 ${EXAMPLE_SOURCES}
 ${EXAMPLE_HEADERS}
)

# Organize in visual studio.
source_group("ExampleGame/src" FILES ${EXAMPLE_SOURCES})
source_group("ExampleGame/include" FILES ${EXAMPLE_HEADERS})

# Link game to the engine and dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE 
Engine
OpenGL::GL
glfw
glad
EnTT::EnTT
imgui
)

#------------------------
# Shader Management
#------------------------
# Copies each .glsl file into build/Assets/shaders/ so ExampleGame can load them at runtime.
file(GLOB EXAMPLE_SHADERS "${GAME_DIR}/Assets/Shaders/*.glsl")
source_group("ExampleGame/Assets/Shaders" FILES ${EXAMPLE_SHADERS})

foreach(shader IN LISTS EXAMPLE_SHADERS)
    get_filename_component(shader_name ${shader} NAME)
    configure_file(
        ${shader}
        ${CMAKE_CURRENT_BINARY_DIR}/Assets/shaders/${shader_name}
        COPYONLY
    )
endforeach()
#------------------------
# Startup Project
#----------------------
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

