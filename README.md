# CppReflectORM

CppReflectORM is a lightweight ORM (Object-Relational Mapping) framework based on C++.

## Setup Instructions

### 1. Unzip Boost Library

After cloning this repository, you should unzip the `boost.zip` file included in the project.

**Recommended Boost Version**:  
We suggest using **Boost 1.84** for compatibility and stability with this project.

### 2. Install MySQL Connector/C++

To install MySQL Connector/C++ on your system, use the following commands:

For **Ubuntu/Debian-based** systems:
```bash
sudo apt update
sudo apt install libmysqlcppconn-dev
```

### 3. Build the Project
After setting up the dependencies, follow these steps to compile the project:

Navigate to the project directory:
```bash
cd CppReflectORM
```

Create a build directory:
```
mkdir build && cd build
```

Run CMake to configure the project:
```bash
cmake ..
```

Build the project using make:
```bash
make
```


## Usage
To use the CppReflectORM framework, follow these steps:

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


## Author Information

**Author**: TaoTao

**Email**: 1017190168@qq.com  

## License and Responsibility Statement

### License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for more details.

### Responsibility Statement

This project is provided as-is, without any warranty of any kind, either express or implied. By using this project, you agree to do so at your own risk. The developer(s) of this project are not responsible for any damage, loss, or negative consequences that may arise from using this project.

### Open Source and Contributions

This project is open-source and encourages collaboration. Developers and users are encouraged to contribute to the improvement of this project. If you find any issues or have suggestions for new features, feel free to open an issue or submit a pull request.

Please follow the general guidelines for contributing to the project and ensure that you adhere to the coding standards and practices used in this repository.

Together, we can make this project even better!

