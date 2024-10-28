#include <iostream>
#include "../dbORM/include/utility.hpp"
#include "../dbORM/include/createTable.hpp"

using namespace std;

struct response
{
    int id;
    std::string name;
    double salary;
};

struct department
{
    int pid;
    std::string name;
    int number;
};

int main()
{
    std::shared_ptr<TableBuilder> builder = std::make_shared<MySQLTableBuilder>();
    TableDirector director(builder);

    department depart;
    std::vector<std::pair<std::string, std::string>> fieldsDepart = utility::getStructFieldsInfo(depart);

    director.construct("department", fieldsDepart,"name");
    std::cout << builder->build() << std::endl;

    response resp;
    std::vector<std::pair<std::string, std::string>> fields = utility::getStructFieldsInfo(resp);

    director.construct("response", fields,"id","name","department(name)");
    std::cout << builder->build() << std::endl;

    return 0;
}
