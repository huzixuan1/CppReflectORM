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

```
### delete

```c
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
    
    UserInformations info;
    std::cout<<remove(info,200)<<std::endl;

    Condition condition("age","<=","240");
    std::cout<<remove_if(info,condition)<<std::endl;;

    return 0;
}

```

### insert

```c
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
```
### select

```c
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
```

### update
```c
#include "../dbORM/include/updateAction.hpp"
#include <iostream>
using namespace updateAction;

// struct UserInfo
// {
//     int age;
//     std::string name;
// };

struct UserInfo
{
    int age;
    std::string name;
    std::string stuId;
};

int main()
{
    // UserInfo user = {30, "Alice"};
    // Condition cond1("age", ">", "25");
    // Condition cond2("name", "=", "Bob");

    // auto updateSql1 = update(user, cond1,"32", "Bob");  // UPDATE UserInfo SET age = '32', name = 'Bob' WHERE age > '25';
    // auto updateSql2 = update(user, cond2,"32", "TaoTao");   // UPDATE UserInfo SET age = '32', name = 'TaoTao' WHERE name = 'Bob';
    // std::cout << updateSql1 << std::endl; 
    // std::cout << updateSql2 << std::endl; 

    UserInfo user = {32, "TaoTao", "30"};
    // std::string condition = "name = 'Bob'"; 
    Condition condition("name","=","tom");
    auto sql = update(user, condition);  
    std::cout << sql << std::endl;

    return 0;
}
```

