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

    auto sql = select("users", Column<std::string>("name"), Column<int>("age")) +
               where(Column<int>("age") > 18) +
               order_by(Column<std::string>("name")) + ";";
    
    // 输出 SQL 语句
    std::cout << sql << std::endl;


    return 0;
}