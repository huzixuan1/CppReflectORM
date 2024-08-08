#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <boost/core/type_name.hpp>

#include <vector>
#include <string>
 
#include <iostream>
 
 
using namespace std;
 
// struct A {
//     friend ostream& operator << (ostream& os, const A &a) { os << "val_a"; return os; }  
// };


struct response
{
    int id;
    double salary;
    string words;
};


template<typename T>
std::vector<std::pair<std::string, std::string>> getStructFieldsInfo(const T& struct_t) {
    std::vector<std::pair<std::string, std::string>> fieldsInfo;

    constexpr auto names = boost::pfr::names_as_array<T>();
    boost::pfr::for_each_field(
        struct_t, [&fieldsInfo, &names](const auto& field, std::size_t idx) {
            std::string typeName = boost::core::type_name<decay_t<decltype(field)>>();
            std::string fieldName = std::string(names[idx]);
            fieldsInfo.emplace_back(fieldName, typeName);
        });

    return fieldsInfo;
}

 
int main() 
{
    response resp;

    std::vector<std::pair<std::string, std::string>> fields = getStructFieldsInfo(resp);

    for (const auto& field : fields) {
        std::cout << "Name: " << field.first << ", Type: " << field.second << std::endl;
    }

    return 0;
}



// #include <boost/pfr/core.hpp>
// #include <boost/pfr/core_name.hpp>
// #include <boost/core/type_name.hpp>
// #include <vector>
// #include <string>
// #include <iostream>
// #include <type_traits>

// using namespace std;

// struct S
// {
//     int i = 1;
//     double d = 2;
//     std::string s = "three";
// };

// struct response
// {
//     int id;
//     double salary;
//     string words;
// };

// template<typename T>
// std::vector<std::pair<std::string, std::string>> getStructFieldsInfo(const T& struct_t) {
//     std::vector<std::pair<std::string, std::string>> fieldsInfo;

//     constexpr auto names = boost::pfr::names_as_array<T>();
//     boost::pfr::for_each_field(
//         struct_t, [&fieldsInfo, &names](const auto& field, std::size_t idx) {
//             std::string typeName = boost::core::type_name<std::decay_t<decltype(field)>>();
//             std::string fieldName = std::string(names[idx]);
//             fieldsInfo.emplace_back(fieldName, typeName);
//         });

//     return fieldsInfo;
// }

// int main() 
// {
//     response r;
//     std::vector<std::pair<std::string, std::string>> fields = getStructFieldsInfo(r);

//     for (const auto& field : fields) {
//         std::cout << "Name: " << field.first << ", Type: " << field.second << std::endl;
//     }

//     return 0;
// }







