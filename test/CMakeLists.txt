# Prefer the system GoogleTest (apt: libgtest-dev); fall back to downloading it.
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

add_executable(autolib_tests
  test_crc8_j1850.cpp
  test_static_ring_buffer.cpp
)
target_link_libraries(autolib_tests PRIVATE autolib GTest::gtest_main)
autolib_set_warnings(autolib_tests)

include(GoogleTest)
gtest_discover_tests(autolib_tests)
