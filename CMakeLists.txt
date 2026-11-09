cmake_minimum_required(VERSION 3.25)
project(ProgrammingProject5 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ProgrammingProject5
    src/main.cpp
    src/work.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(ProgrammingProject5 PRIVATE Threads::Threads)

if(MSVC)
    target_compile_options(ProgrammingProject5 PRIVATE /W4 /EHsc /permissive- /Zc:__cplusplus /utf-8)
else()
    target_compile_options(ProgrammingProject5 PRIVATE -Wall -Wextra -Wpedantic)
endif()