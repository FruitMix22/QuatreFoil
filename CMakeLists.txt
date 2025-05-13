cmake_minimum_required(VERSION 3.15)
project(GDP)

# OOOKAAAAAAAAAAY :
# KEEP THIS NEAT.
# ADD FILES AS NECCESSARY.
# GET USED TO IT BEING CONFUSING.
# EXPECT IT TO BREAK EVERY OTHER DAY.   


#------------------------*
# Dependencies
#------------------------*
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

include(FetchContent)
FetchContent_Declare(entt 
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.12.2
)
FetchContent_MakeAvailable(entt)

#------------------------*
# ImGui (docking branch)
#------------------------*
FetchContent_Declare(
    imgui
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

# Enable docking support
target_compile_definitions(imgui PUBLIC IMGUI_ENABLE_DOCKING)

#------------------------*
# Engine Library
#------------------------*
add_library(Engine STATIC
    # Core
    Engine/Core/include/EngineCore.hpp
    Engine/Core/include/Layer.hpp
    Engine/Core/include/Input.hpp

    Engine/Core/src/EngineCore.cpp
    Engine/Core/src/Input.cpp
    
    # Buffers
    Engine/Buffers/include/VBO.hpp
    Engine/Buffers/include/VAO.hpp
    Engine/Buffers/include/EBO.hpp
    Engine/Buffers/include/FBO.hpp

    Engine/Buffers/src/VBO.cpp
    Engine/Buffers/src/VAO.cpp
    Engine/Buffers/src/EBO.cpp
    Engine/Buffers/src/FBO.cpp
    
    # Renderer
    Engine/Renderer/include/Renderer.hpp
    Engine/Renderer/include/ImGuiLayer.hpp
    Engine/Renderer/include/Shader.hpp
    Engine/Renderer/include/Texture.hpp
    Engine/Renderer/include/Camera.hpp
    Engine/Renderer/include/Quad.hpp

    Engine/Renderer/src/Renderer.cpp
    Engine/Renderer/src/ImGuiLayer.cpp
    Engine/Renderer/src/Shader.cpp
    Engine/Renderer/src/Texture.cpp
    Engine/Renderer/src/Camera.cpp
    Engine/Renderer/src/Quad.cpp
    
    # Components
    Engine/Components/Renderable.hpp
    Engine/Components/Transform.hpp
    Engine/Components/Player.hpp
    #Engine/Components/Camera.hpp
)

# Public includes
target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine
    ${GLAD_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw/include
    $<TARGET_PROPERTY:EnTT::EnTT,INTERFACE_INCLUDE_DIRECTORIES>
    ${imgui_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/stb
)

target_compile_definitions(Engine PUBLIC IMGUI_ENABLE_DOCKING)

target_link_libraries(Engine PRIVATE
    OpenGL::GL
    glfw
    glad
    EnTT::EnTT
    imgui
)

#--------------------------------*
# Solution Explorer Organization 
#--------------------------------*

# Core 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Core/include PREFIX "Engine/Core/include" FILES
    Engine/Core/include/EngineCore.hpp
    Engine/Core/include/Layer.hpp
    Engine/Core/include/Input.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Core/src PREFIX "Engine/Core/src" FILES
    Engine/Core/src/EngineCore.cpp
    Engine/Core/src/Input.cpp
)

# Buffers 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Buffers/include PREFIX "Engine/Buffers/include" FILES
    Engine/Buffers/include/VBO.hpp
    Engine/Buffers/include/VAO.hpp
    Engine/Buffers/include/EBO.hpp
    Engine/Buffers/include/FBO.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Buffers/src PREFIX "Engine/Buffers/src" FILES
    Engine/Buffers/src/VBO.cpp
    Engine/Buffers/src/VAO.cpp
    Engine/Buffers/src/EBO.cpp
    Engine/Buffers/src/FBO.cpp
)

# Renderer 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/include PREFIX "Engine/Renderer/include" FILES
    Engine/Renderer/include/Renderer.hpp
    Engine/Renderer/include/ImGuiLayer.hpp
    Engine/Renderer/include/Shader.hpp
    Engine/Renderer/include/Texture.hpp
    Engine/Renderer/include/Camera.hpp
    Engine/Renderer/include/Quad.hpp
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Renderer/src PREFIX "Engine/Renderer/src" FILES
    Engine/Renderer/src/Renderer.cpp
    Engine/Renderer/src/ImGuiLayer.cpp
    Engine/Renderer/src/Shader.cpp
    Engine/Renderer/src/Texture.cpp
    Engine/Renderer/src/Camera.cpp
    Engine/Renderer/src/Quad.cpp
)

# Components 
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/Engine/Components PREFIX "Engine/Components" FILES
    Engine/Components/Renderable.hpp
    Engine/Components/Transform.hpp
    Engine/Components/Player.hpp
    #Engine/Components/Camera.hpp
)

#------------------------*
# Game Project
#------------------------*

# Explicitly add headers to source group for better VS integration
file(GLOB QUATREFOIL_HEADERS "QuatreFoil/include/*.hpp")

# Include the headers in the 'include' folder for QuatreFoil project
include_directories(QuatreFoil/include)

source_group("include" FILES ${QUATREFOIL_HEADERS})
source_group("src" FILES ${QUATREFOIL_SOURCES})

set(QUATREFOIL_SOURCES
    QuatreFoil/src/QuatreFoil.cpp
    QuatreFoil/src/EntryPoint.cpp
)

add_executable(QuatreFoil ${QUATREFOIL_SOURCES} ${QUATREFOIL_HEADERS})

source_group("src" FILES ${QUATREFOIL_SOURCES})
source_group("include" FILES ${QUATREFOIL_HEADERS})



target_link_libraries(QuatreFoil PRIVATE 
Engine
OpenGL::GL
glfw
glad
EnTT::EnTT
imgui
)

#------------------------*
# Shader Management
#------------------------*
file(GLOB QUATREFOIL_SHADERS "QuatreFoil/Assets/Shaders/*.glsl")
source_group("Assets\\Shaders" FILES ${QUATREFOIL_SHADERS})

foreach(shader ${QUATREFOIL_SHADERS})
    get_filename_component(shader_name ${shader} NAME)
    configure_file(${shader} ${CMAKE_CURRENT_BINARY_DIR}/Assets/shaders/${shader_name} COPYONLY)
endforeach()

#------------------------*
# Startup Project
#------------------------*
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT QuatreFoil)
