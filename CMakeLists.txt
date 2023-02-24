cmake_minimum_required(VERSION 3.0.0)
project(echo VERSION 0.1.0)

include (etc/build_defs.cmake)
include (etc/build_type.cmake)

add_subdirectory(src/libnetcapture)
add_subdirectory(src/app)