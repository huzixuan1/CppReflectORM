cmake_minimum_required(VERSION 3.5)
project(dbORM)

set(CMAKE_CXX_STANDARD 20)

# include_directories(/home/huzixuan/workSpaces/CppReflectDB)
include_directories(${CMAKE_SOURCE_DIR}/../CppReflectDB)

# add_executable(dbORM dbORM/createTable.cpp)
# add_executable(dbORM dbORM/src/createTable.cpp)
add_executable(dbORM dbORM/insertData.cpp)

# target_link_libraries(dbORM PRIVATE ${CMAKE_DL_LIBS} -lmariadbclient)