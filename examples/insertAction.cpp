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

int main()
{

    Temp user;
    // need to improve as below:
    // Tem user = {1,20.0,230.0,"tom"};     

    auto sql = insert(user,"1","50.0","230.0","tom");       // INSERT INTO Temp(id, weight, salary, userName) VALUES ('1', '50.0', '230.0', 'tom');
    std::cout<<sql<<std::endl;



    return 0;
}