#include "../dbORM/include/deleteAction.hpp"
#include <iostream>
using namespace deleteAction;

struct UserInformations
{
    int age;
    std::string name;
};

int main()
{

    // DELETE FROM UserInformations WHERE id = 200;
    // DELETE FROM UserInformations WHERE age != '2564';
    
    auto table_name = get_table_name<UserInformations>();
    std::cout<<table_name<<std::endl;

    auto sql = remove<UserInformations>(200);
    std::cout<<sql<<std::endl;

    Condition condition("age","!=","2564");
    auto condition_sql = remove_if<UserInformations>(condition);
    std::cout<<condition_sql<<std::endl;


    return 0;
}