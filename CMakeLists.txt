cmake_minimum_required(VERSION 3.16)
project(MyGLApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GLAD
add_library(glad glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

# GLFW - vendored
add_subdirectory(extern/glfw)

# Executable
add_executable(output main.cpp)

# Include dirs
target_include_directories(output PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(output PRIVATE
    glad
    glfw
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
)

add_custom_target(balls
    COMMAND ./output 
    DEPENDS output
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
