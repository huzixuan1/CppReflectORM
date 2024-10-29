#ifndef CREATE_ACTION_HPP
#define CREATE_ACTION_HPP

#include <sstream>
#include <vector>
#include "utility.hpp"

namespace createAction
{


    // 1.create table tableName (student_id INT,name VARCHAR(50),age INT);
    template<typename T>
    std::string createTable(const T& struct_)
    {
        std::ostringstream sql;
        sql<<"CREATE TABLE "<<utility::get_table_name<T>()<< " (";
        std::vector<std::pair<std::string,std::string>> fieldInfo = utility::getStructFieldsInfo(struct_);
        for(size_t i = 0;i<fieldInfo.size();i++)
        {
            const auto& it = fieldInfo[i];
            sql <<it.first<<" "<<it.second;
            if(i<fieldInfo.size()-1)
            {
                sql<<", ";
            }
        }   // for

        sql<<");";

        return sql.str();
    }



};


#endif  // CREATE_ACTION_HPP