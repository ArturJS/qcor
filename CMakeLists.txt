cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_DISABLE_IN_SOURCE_BUILDS ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)
set(CLANG_COMPILER /usr/bin/clang++-9)

project(qcor LANGUAGES CXX)

option(QCOR_BUILD_TESTS "Build qcor tests" OFF)

find_package(Clang 9.0.0 REQUIRED)
find_package(XACC REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/scripts/qcor.in
               ${CMAKE_BINARY_DIR}/qcor)
include_directories(/home/cades/dev/llvm-project/clang/include)
add_subdirectory(runtime)
add_subdirectory(compiler)
add_subdirectory(ir)

install(PROGRAMS ${CMAKE_BINARY_DIR}/qcor DESTINATION bin)
