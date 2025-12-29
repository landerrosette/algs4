cmake_minimum_required(VERSION 3.21)
project(algs4)

add_library(algs4 INTERFACE)
target_include_directories(algs4 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(algs4 INTERFACE cxx_std_20)

option(ALGS4_BUILD_CLIENTS "Build clients" ${PROJECT_IS_TOP_LEVEL})
if (ALGS4_BUILD_CLIENTS)
    add_subdirectory(clients)
endif ()
