cmake_minimum_required(VERSION 3.14)
project(CitrusDB)

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0135 NEW)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/d25e625364a2078c940da2cb1fcf098aa184fd9f.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Find asio
set(ASIO_INCLUDE_DIR /home/linuxbrew/.linuxbrew/opt/asio/include)
list(APPEND CMAKE_MODULE_PATH /home/linuxbrew/.linuxbrew/opt/Crow/cmake)
find_package(asio REQUIRED)

# Add CrowCpp
find_package(Crow REQUIRED)

# Find Boost
set(Boost_INCLUDE_DIR /home/linuxbrew/.linuxbrew/opt/boost/include)
find_package(Boost REQUIRED COMPONENTS system)

FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.0+5 
)
FetchContent_MakeAvailable(crow)


enable_testing()
add_executable(
  # testHarness
  # backend/jsonStrings.cpp
  # backend/file.cpp
  # test.cpp
  main
  ./frontend/citrusdb/src/components/API/main.cpp
)


add_test(
  NAME testHarness
  COMMAND testHarness ${CMAKE_CURRENT_SOURCE_DIR}/database/people.json
)

# target_link_libraries(
#   testHarness
#   GTest::gtest_main
# )
target_include_directories(main PRIVATE  ${crow_SOURCE_DIR}/include)

target_link_libraries(main PRIVATE Boost::system)

include(GoogleTest)
# gtest_discover_tests(testHarness)
include_directories(json-develop/include)