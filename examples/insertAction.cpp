#include <iostream>
#include "../dbORM/include/insertAction.hpp"
using namespace insertAction;


struct Temp
{
    int id;
    double weight;
    double salary;
    std::string userName;
};


struct UserInfo
{

    int id;
    std::string name;
    int stuId;
};

int main()
{

    // Temp user;
    // need to improve as below:
    Temp user = {1,20.0,230.0,"tom"};     

    // auto sql = insert(user,"1","50.0","230.0","tom");       // INSERT INTO Temp(id, weight, salary, userName) VALUES ('1', '50.0', '230.0', 'tom');
    auto sql = insert(user);       // INSERT INTO Temp(id, weight, salary, userName) VALUES ('1', '50.0', '230.0', 'tom');
    std::cout<<sql<<std::endl;

    UserInfo info = {61511,"tom",30};
    std::cout<<insert(info)<<std::endl;

    return 0;
}
