cmake_minimum_required(VERSION 3.16)
project(serialization-compare)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_subdirectory(third_party)
add_subdirectory(common)
add_subdirectory(worker)
add_subdirectory(proxy)
