cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ..)
set(FILE
        src/main.cpp
        src/Parsing.cpp
        src/Renderer.cpp
        src/SceneBuilder.cpp
    )
set(INCLUDE_DIRS
        ./include
        ./include/interfaces
)

add_executable(raytracer ${FILE})
target_link_libraries(raytracer
        sfml-graphics sfml-window sfml-system sfml-audio -lconfig++
    )
target_include_directories(raytracer PRIVATE ${INCLUDE_DIRS} )
add_compile_options(-Wall -Wextra -Werror -g3)
