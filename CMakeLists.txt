cmake_minimum_required(VERSION 3.24)
project(ray_tracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ray_tracing main.cpp vec3.h color.h ray.h entity.h sphere.h entity_list.h util.h camera.h material.h)
