cmake_minimum_required(VERSION 3.30)
project(Nebula VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

# Detecta compilador e força runtime estático no Windows
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()

# Diretório das dependências externas
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/external")
include(FetchContent)

# GLFW
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
)
FetchContent_MakeAvailable(glm)

# STB Image (header-only)
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG master
)
FetchContent_MakeAvailable(stb)

# Fontes principais
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Nebula ${SOURCES}
        src/SandBox/sandbox.cpp
        src/Nebula/Window.cpp
        src/Nebula/Application.cpp
        src/Nebula/Renderer.cpp
        src/Nebula/Shader.cpp
        src/Nebula/Shader.h
        src/Nebula/Mesh.cpp
        src/Nebula/Mesh.h
        src/Nebula/Vertex.h
        src/Nebula/VBO.cpp
        src/Nebula/VBO.h
        src/Nebula/VAO.cpp
        src/Nebula/VAO.h
        src/Nebula/EBO.cpp
        src/Nebula/EBO.h
        src/Nebula/Camera.cpp
        src/Nebula/Camera.h
)

find_package(OpenGL REQUIRED)

target_link_libraries(Nebula
        PRIVATE
        glfw
        OpenGL::GL
        glad
        glm::glm
)

# Incluir diretórios das libs externas
target_include_directories(Nebula
        PRIVATE
        ${glfw_SOURCE_DIR}/include
        ${glad_SOURCE_DIR}/include
        ${glm_SOURCE_DIR}
        ${stb_SOURCE_DIR}
)

# Copia shaders para a pasta de saída
file(GLOB SHADERS "${CMAKE_SOURCE_DIR}/src/shaders/*.glsl")
foreach(SHADER ${SHADERS})
    get_filename_component(FILENAME ${SHADER} NAME)
    configure_file(${SHADER} "${CMAKE_BINARY_DIR}/shaders/${FILENAME}" COPYONLY)
endforeach()
