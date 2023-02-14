cmake_minimum_required (VERSION 3.23)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(PathTracing)

set(CMAKE_CXX_STANDARD 11)

set(
    SOURCES
    src/main.cpp
    src/vector.h
    src/vector.cpp
    src/string_reader.h
    src/string_reader.cpp
    src/camera.h
    src/camera.cpp
    src/light.h
    src/light.cpp
    src/tiny_obj_loader.h
    src/tiny_obj_loader.cpp
    src/object.h
    src/object.cpp
    src/renderer.h
    src/renderer.cpp
    src/bvh_node.h
    src/bvh_node.cpp
    src/bvh_tree.h
    src/bvh_tree.cpp
    src/picture_io.h
    src/picture_io.cpp
)

add_executable(PathTracing ${SOURCES})