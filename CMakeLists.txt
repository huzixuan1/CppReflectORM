cmake_minimum_required(VERSION 3.5)
project(dbORM)

set(CMAKE_CXX_STANDARD 20)

# message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
include_directories(${CMAKE_SOURCE_DIR})

# test for dbORM
# add_executable(dbORM dbORM/deleteData.cpp)   
# test for include
add_executable(dbORM examples/update.cpp)     

# target_link_libraries(dbORM PRIVATE ${CMAKE_DL_LIBS} -lmariadbclient)