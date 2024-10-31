# CppReflectORM
CppReflectORM is a lightweight ORM (Object-Relational Mapping) framework based on CPP

1.after clone this repo,you should to unzip boost.zip

2.install connector/c++

sudo apt update

sudo apt install libmysqlcppconn-dev

## using
### create table
```c
#include "../dbORM/include/createAction.hpp"
#include <iostream>

using namespace createAction;

struct StudentInfo
{
    int id;
    std::string name;
    int age;
};


int main()
{
    // CREATE TABLE StudentInfo (id INTEGER, name VARCHAR(255), age INTEGER);
    StudentInfo instance;
    auto sql = createTable(instance);
    std::cout<<sql<<std::endl;

    return 0;
}


