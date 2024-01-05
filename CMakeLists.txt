cmake_minimum_required(VERSION 3.10)

project(Raytracing VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Raytracing
    main.cc
    camera.cc
    color.cc
    hittable_list.cc
    material.cc
    ray.cc
    sphere.cc
    vec3.cc
)
