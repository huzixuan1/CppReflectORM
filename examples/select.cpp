#include "../dbORM/include/queryAction.hpp"
#include <iostream>
using namespace selectAction;

struct User
{
    int age;
    std::string name;
};

int main()
{
    User user;
    Condition condition("age",">","25");
    auto sql = create(user,condition,"age","name"); // SELECT age, name FROM User WHERE age > '25';

    std::cout<<sql<<std::endl;

    return 0;
}