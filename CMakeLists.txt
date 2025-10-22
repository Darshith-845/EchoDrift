cmake_minimum_required(VERSION 3.10)
project(EchoDrift)

# Use modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Include header directories
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    include
)

# Collect all .cpp files from src/
file(GLOB_RECURSE SRC_FILES 
    "src/*.cpp" 
)
# Create executable
add_executable(EchoDrift ${SRC_FILES})

# Link libraries
target_link_libraries(EchoDrift
    ${OPENGL_LIBRARIES}
    GLEW::GLEW
    glfw
)
