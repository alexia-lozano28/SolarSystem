cmake_minimum_required(VERSION 3.10)
project(SolarSystem)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 REQUIRED)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(SolarSystem
    src/main.cpp
    src/Shader.cpp
    src/Sphere.cpp
    src/Camera.cpp
    src/Planet.cpp
)

target_link_libraries(SolarSystem glfw "-framework OpenGL")
