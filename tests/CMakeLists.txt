# g++ example.cpp -lgtest -lgtest_main

cmake_minimum_required(VERSION 3.5)
project(ormTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
include_directories(${CMAKE_SOURCE_DIR}/../)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../dbORM/include)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ormTest 
    src/executeUT.cpp
    src/tableBuilderTest.cpp
    ../dbORM/src/createTable.cpp
    )

# target_link_libraries(dbORM GTest::GTest GTest::Main pthread)

target_link_libraries(ormTest -lgtest -lgtest_main)

