cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project(TextQuery LANGUAGES CXX)

file(GLOB_RECURSE src CONFIGURE_DEPENDS src/*.cc src/*.h)
add_executable(text_query ${src})

