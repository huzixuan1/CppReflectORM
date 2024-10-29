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