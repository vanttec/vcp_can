cmake_minimum_required(VERSION 3.1)

project(VCP_CAN VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(vcp_can SHARED src/vcp_can.cpp)
target_include_directories(vcp_can PUBLIC ${CMAKE_SOURCE_DIR}/include)
