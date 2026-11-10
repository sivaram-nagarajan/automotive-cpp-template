cmake_minimum_required(VERSION 3.20)
project(autolib VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(AUTOLIB_BUILD_TESTS "Build unit tests" ON)
option(AUTOLIB_COVERAGE "Instrument for code coverage (GCC/Clang)" OFF)
option(AUTOLIB_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

include(cmake/CompilerWarnings.cmake)

add_library(autolib
  src/crc8_j1850.c
)
target_include_directories(autolib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
autolib_set_warnings(autolib)

if(AUTOLIB_COVERAGE)
  target_compile_options(autolib PRIVATE --coverage -O0)
  target_link_options(autolib PUBLIC --coverage)
endif()

if(AUTOLIB_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
