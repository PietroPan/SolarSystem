cmake_minimum_required(VERSION 3.5)

project(generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
               generator.cpp
               generator.h
               utils/model.cpp
               utils/model.h
               utils/point.h
               models/box.cpp
               models/box.h
               models/cone.cpp
               models/cone.h
               models/sphere.cpp
               models/sphere.h
               models/plane.cpp
               models/plane.h
               models/bezier.cpp
               models/bezier.h)
