#include <string>
#include <iostream>
#include <type_traits>

/**
 * This cppToSql for Transforms c++ type to sql,
 * like int -> INTEGER ...
 */

namespace cppToSql{

    // template<class T,typename Enable = void>
    // struct TypeConverter
    // {
    //     /* data */
    // };

    template<class T,typename Enable = void>
    struct TypeConverter
    {
        static std::string& converter(){
            static_assert(sizeof(T) == 0,"TypeConverter not implatemented for this type !");
            static std::string empty;
            return empty;
        }
    };

    template<>
    struct TypeConverter<int>
    {
        static const std::string& converter() {
            static const std::string res = "INTEGER";
            return res;
        } 
    };

    template<>
    struct TypeConverter<std::string>
    {
        static const std::string& converter(){
            static const std::string res = "TEXT";
            return res;
        }
    };

    template<>
    struct TypeConverter<double>
    {
        static const std::string& converter(){
            static const std::string res = "REAL";
            return res;
        }
    };

    template<>
    struct TypeConverter<float>
    {
        static const std::string& converter(){
            static const std::string res = "FLOAT";
            return res;
        }
    };

    // Other type to Transforms...

};

int main()
{
    std::cout << cppToSql::TypeConverter<int>::converter() << std::endl; // 输出 "INTEGER"
    std::cout << cppToSql::TypeConverter<double>::converter() << std::endl; // 输出 "REAL"
    std::cout << cppToSql::TypeConverter<float>::converter() << std::endl; // 输出 "FLOAT"


    std::cout << cppToSql::TypeConverter<bool>::converter() << std::endl; // 输出 "ERROR"
    


    return 0;
}