cmake_minimum_required (VERSION 3.23)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#set(OPENMP_LIBRARIES "/opt/homebrew/Cellar/libomp/14.0.5/lib")
#set(OPENMP_INCLUDES "/opt/homebrew/Cellar/libomp/14.0.5/include")

project(PathTracing)

set(CMAKE_CXX_STANDARD 11)

#find_package(OpenMP REQUIRED)
#if (OPENMP_FOUND)
#    include_directories("${OPENMP_INCLUDES}")
#    link_directories("${OPENMP_LIBRARIES}")
#    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif(OPENMP_FOUND)

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
)

add_executable(PathTracing ${SOURCES})