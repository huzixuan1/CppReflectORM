#include <string>
#include <vector>
#include <iostream>
#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <boost/core/type_name.hpp>

using namespace std;

template<typename T>
std::string convertToString(const T& value)
{
    return std::to_string(value);
}

template<>
std::string convertToString(const std::string& value)
{
    return value;
}

template<typename T>
std::vector<std::pair<std::string, std::string>> getStructFieldsInfo(const T& struct_t) {
    std::vector<std::pair<std::string, std::string>> fieldsInfo;

    constexpr auto names = boost::pfr::names_as_array<T>();
    boost::pfr::for_each_field(
        struct_t, [&fieldsInfo, &names](const auto& field, std::size_t idx) {
            std::string value = convertToString(field);
            std::string fieldName = std::string(names[idx]);
            fieldsInfo.emplace_back(fieldName, value);
        });

    return fieldsInfo;
}

// insert into tableName (id,weight,salary,userName) values (1,50,230,,tom);
template<typename T>
std::string generateSQL(const T& struct_t, std::string tableName) {
    std::vector<std::pair<std::string, std::string>> fields = getStructFieldsInfo(struct_t);
    std::string sql = "insert into " + tableName + " (";
    std::string values = "values (";

    for (const auto& field : fields) {
        sql += field.first + ",";
        values += "'" + field.second + "',";
    }

    sql.pop_back();     // delete the last ,
    values.pop_back();

    sql += ") " + values + ");";

    return sql;
}


struct insertData
{
    /* data */
    int id;
    float weight;
    double salary;
    std::string userName;
};



int main()
{
    insertData obj;
    obj.id = 1;
    obj.weight = 50;
    obj.salary = 2300;
    obj.userName = "tom";

    // auto fields = getStructFieldsInfo(obj);
    // for(const auto& field:fields)
    // {
    //     std::cout << "Name: " << field.first << ", Value: " << field.second << std::endl;
    // }

    std::cout<<generateSQL(obj,"userName")<<std::endl;
    return 0;
}
