cmake_minimum_required(VERSION 3.21)
project(c___demo)

set(CMAKE_CXX_STANDARD 17)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(c___demo main.cpp Asteroid.cpp Asteroid.h Ship.cpp Ship.h ShaderProgram.cpp ShaderProgram.h Matrix.cpp Matrix.h Bullet.cpp Bullet.h Bullets.cpp Bullets.h Asteroids.cpp Asteroids.h)

target_link_libraries(c___demo GLEW::GLEW)
target_link_libraries(c___demo glfw)
target_link_libraries(c___demo OpenGL::GL)

file(COPY resources DESTINATION .)