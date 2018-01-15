# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

#Project's Name
project(graph_coloring)

#Set Output folder where program will be created
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#Find Boost Package
find_package(Boost REQUIRED)

if (Boost_FOUND)
    #message(STATUS "Found Boost")
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost not found")
endif()

#Set to C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp") #-fast -qopenmp")

#Set Intel Compilers
#set(CMAKE_C_COMPILER icc)
#set(CMAKE_CXX_COMPILER icpc)

#The following folders will be included
include_directories("${PROJECT_SOURCE_DIR}/src")

file(GLOB CXX_SOURCES src/algorithms/*.cpp)

#set(KMP_AFFINITY='verbose,proclist=[9,8,15,14]')

add_executable(graph_coloring src/main.cpp)
# src/rokos.cpp src/greedy.cpp src/greedy-lu.cpp src/catalyurek.cpp src/sched-rev.cpp src/check_coloring.cpp
               #src/get_color_stats.cpp)


target_link_libraries(graph_coloring ${Boost_LIBRARIES} ${CXX_SOURCES})