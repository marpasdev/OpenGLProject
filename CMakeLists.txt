cmake_minimum_required(VERSION 3.20)

project(OpenGLProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(glad STATIC
    external/glad/src/gl.c
)

target_include_directories(glad
    PUBLIC
        ${PROJECT_SOURCE_DIR}/external/glad/include
)

set(SHADER_FILES
    ${PROJECT_SOURCE_DIR}/shaders/vertex/basic.vert
    ${PROJECT_SOURCE_DIR}/shaders/fragment/basic.frag
)

add_executable(OpenGLProject
    src/main.cpp
    src/shader.cpp
    src/shaderprogram.cpp
    ${SHADER_FILES}
)

target_include_directories(OpenGLProject
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(OpenGLProject
    PRIVATE
        glad
        glfw
        OpenGL::GL
)

add_custom_command(TARGET OpenGLProject POST_BUILD  
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:OpenGLProject>/assets
)

add_custom_command(TARGET OpenGLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:OpenGLProject>/shaders
)