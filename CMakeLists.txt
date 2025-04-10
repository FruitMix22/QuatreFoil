cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(GDP)

# Dependencies
add_subdirectory(externals/glfw)
add_library(glad STATIC externals/glad/src/glad.c)
target_include_directories(glad PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include
)
find_package(OpenGL REQUIRED)

# 2DRenderer 
file(GLOB 2DRENDERER_HEADERS "2DRenderer/include/*.hpp")
file(GLOB 2DRENDERER_SOURCES "2DRenderer/src/*.cpp")

add_library(EngineCore STATIC
    ${2DRENDERER_SOURCES}
    ${2DRENDERER_HEADERS}
)
target_include_directories(EngineCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/2DRenderer/include
)
target_link_libraries(EngineCore
    OpenGL::GL
    glfw
    glad
)

# QuatreFoil
file(GLOB QUATREFOIL_SOURCES "QuatreFoil/src/*.cpp")
file(GLOB QUATREFOIL_HEADERS "QuatreFoil/include/*.hpp")

# Find all shader files
file(GLOB_RECURSE QUATREFOIL_SHADERS 
    "QuatreFoil/Assets/Shaders/*.glsl"
)

add_executable(QuatreFoil
    ${QUATREFOIL_SOURCES}
    ${QUATREFOIL_HEADERS}
)
target_link_libraries(QuatreFoil PRIVATE EngineCore)
target_include_directories(QuatreFoil PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/2DRenderer/include
)

# Solution Explorer Organization
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/2DRenderer PREFIX "Engine" FILES
    ${2DRENDERER_SOURCES}
    ${2DRENDERER_HEADERS}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/QuatreFoil PREFIX "Game" FILES
    ${QUATREFOIL_SOURCES}
    ${QUATREFOIL_HEADERS}
)

# Add shaders to Solution Explorer under Assets group
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/QuatreFoil/Assets PREFIX "Assets" FILES
        ${QUATREFOIL_SHADERS}
    )

# Copy shaders to build directory
foreach(shader ${QUATREFOIL_SHADERS})
    get_filename_component(shader_name ${shader} NAME)
    configure_file(${shader} ${CMAKE_CURRENT_BINARY_DIR}/Assets/shaders/${shader_name} COPYONLY)
endforeach()

# Make game the startup
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT QuatreFoil)