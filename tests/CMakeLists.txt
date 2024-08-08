# g++ example.cpp -lgtest -lgtest_main

cmake_minimum_required(VERSION 3.5)
project(ormTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/../CppReflectDB)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ormTest src/example.cpp)

# target_link_libraries(dbORM GTest::GTest GTest::Main pthread)

target_link_libraries(ormTest -lgtest -lgtest_main)

