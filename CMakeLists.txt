cmake_minimum_required(VERSION 3.14)
project(CitrusDB)

set(CMAKE_CXX_STANDARD 17)

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
  backend/readFile.cpp
  backend/deleteFile.cpp
  backend/uploadFile.cpp
  backend/jsonStrings.cpp
  test.cpp
)

add_test(
  NAME testHarness
  COMMAND testHarness ${CMAKE_CURRENT_SOURCE_DIR}/database/people.json
)

target_link_libraries(
  testHarness
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(testHarness)
include_directories(json-develop/include)
