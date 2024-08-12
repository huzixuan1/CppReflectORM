cmake_minimum_required(VERSION 3.5)
project(dbDemo)

set(CMAKE_CXX_STANDARD 20)
include_directories(${CMAKE_SOURCE_DIR}/../../CppReflectDB)
# add_executable(dbDemo src/codeForCreateTable.cpp)

add_executable(dbDemo src/insertData.cpp)

# target_link_libraries(dbORM PRIVATE ${CMAKE_DL_LIBS} -lmariadbclient)