#include "../dbORM/include/updateAction.hpp"
#include <iostream>
using namespace updateAction;

struct UserInfo
{
    int age;
    std::string name;
};

int main()
{
    UserInfo user = {30, "Alice"};
    Condition cond1("age", ">", "25");
    Condition cond2("name", "=", "Bob");

    auto updateSql1 = update(user, cond1,"32", "Bob");  // UPDATE UserInfo SET age = '32', name = 'Bob' WHERE age > '25';
    auto updateSql2 = update(user, cond2,"32", "TaoTao");   // UPDATE UserInfo SET age = '32', name = 'TaoTao' WHERE name = 'Bob';
    std::cout << updateSql1 << std::endl; 
    std::cout << updateSql2 << std::endl; 

    return 0;
}