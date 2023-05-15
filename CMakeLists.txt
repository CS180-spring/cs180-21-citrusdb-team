cmake_minimum_required(VERSION 3.14)
project(CitrusDB)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/d25e625364a2078c940da2cb1fcf098aa184fd9f.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  testHarness
  backend/file.cpp
  backend/databaseEngine.cpp
  test.cpp
)

target_link_libraries(
  testHarness
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(testHarness)
