cmake_minimum_required(VERSION 2.8)

project(image_seg)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE "debug")
set(CMAKE_CXX_FLAGS "-std=c++11 -march=native")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

find_package(OpenCV 3.1 REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
