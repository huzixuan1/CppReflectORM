
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "boost/pfr/core.hpp"
#include "boost/pfr/core_name.hpp"
#include "boost/core/type_name.hpp"
using namespace std;

class MariadbHelper
{
    public:

        // create table tableName (id INT,salary INT,config VARCHAR(255));
        template<typename T>
        std::string createTable(const T& info, const std::string& tableName)
        {
            constexpr auto names = boost::pfr::names_as_array<T>();
            stringstream sql;
            sql << "CREATE TABLE vonu_Aggregator." << tableName << " (";

            boost::pfr::for_each_field(
                info, [&](const auto& field, std::size_t idx)
                {
                    std::string typeNameStr = boost::core::type_name<decay_t<decltype(field)>>();

                    sql << names[idx] << " " << typeToSqlType(typeNameStr);

                    if (idx != boost::pfr::tuple_size<T>::value - 1) {
                        sql << ", ";
                    }
                });

            sql << ");";
            return sql.str();
        }

        // replace into tableName (id,salary,config) values (?,?,?);
        template<typename T>
        std::string generateSQLForSetData(const T& info, const std::string& tableName)
        {
            constexpr auto names = boost::pfr::names_as_array<T>();
            std::stringstream sql;
            sql << "REPLACE INTO vonu_Aggregator." << tableName << " (";

            boost::pfr::for_each_field(info, [&](const auto& field, std::size_t idx) {
                sql << names[idx];
                if(idx != boost::pfr::tuple_size<T>::value - 1) {
                    sql << ",";
                }
            });

            sql << ") VALUES (";

            boost::pfr::for_each_field(info, [&](const auto& field, std::size_t idx) {
                sql << field;
                if(idx != boost::pfr::tuple_size<T>::value - 1) {
                    sql << ",";
                }
            });

            sql << ");";

            return sql.str();
        }

        // update tableName set key = value where key = ;
        std::string generateSQLForUpdateData(const std::string& tableName,std::string &&key,std::string &&value,std::string &&old_key,std::string &&old_value)
        {
            std::stringstream sql;
            sql << "UPDATE vonu_Aggregator."<<tableName<<" set "<<key<<" = "<<value<<" where "<<old_key<< " = "<<old_value;
            return sql.str();
        }

        std::string generateSQLForGetData(const std::string& tableName)
        {
            std::stringstream sql;
            sql << "SELECT *FROM vonu_Aggregator."<<tableName<<";";
            return sql.str(); 
        }

    private:
        std::string typeToSqlType(std::string& info)
        {
           if(info == "int")
           {
                return "INT";
           }else if(info == "double"){
                return "BLOB";
           }else if(info == "std::string"){
                return "VARCHAR(255)";
           }else if(info == "string"){
                return "VARCHAR(255)";
           }else{
            return "";
           }
        }
};




struct UserData
{
    int id = 1;
    double salary = 2000.0;
    std::string config = "config";
};


struct UserDataA
{
    std::string name;
    std::string cofig;
};

struct UserDataB
{
    std::string sn;
    UserDataA data;
};


void apiTest()
{

    // createTableSQL
    UserData data;
    MariadbHelper obj;
    auto createTableSQL = obj.createTable(data,"onudata");
    std::cout<<createTableSQL<<std::endl;

    // setData
    data.id = 30;
    auto setDataSQL = obj.generateSQLForSetData(data,"onudata");
    std::cout<<setDataSQL<<std::endl;

    // update Data
    auto updateSQL = obj.generateSQLForUpdateData("onudata","id","4","id","1");
    std::cout<< updateSQL << std::endl;

    // getData
    auto selectSQL = obj.generateSQLForGetData("onudata");
    std::cout<<selectSQL<<std::endl;


    // MariadbHelper obj;
    // auto getData = obj.generateSQLForGetData("onudata");
    // std::cout<<getData<<std::endl;


    // std::unordered_map<std::string,std::string> all_data;
    // if(mgnt_ptr->getAllData(obj.generateSQLForGetData("onudata"),all_data)){
    //     for(const auto& pair:all_data){
    //         std::cout<<"key:"<<pair.first<<", value:"<<pair.second<<std::endl;
    //     }
    // }else{
    //     std::cout<<"Failed to execute SQL qurey."<<std::endl;
    // }

    // auto result = all_data["copy"];
    // std::cout<<result<<std::endl;
    

}



int main()
{

    apiTest();

    return 0;
}

