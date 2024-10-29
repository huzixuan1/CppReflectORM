#ifndef INSERT_ACTION_HPP
#define INSERT_ACTION_HPP

#include "utility.hpp"
#include <sstream>
#include <vector>
#include <string>
namespace insertAction
{

    // insert into tableName (id,weight,salary,userName) values (1,50,230,tom);
    template<typename T,typename...Args>
    std::string insert(const T& struct_,Args...args)
    {

        std::ostringstream sql;
        sql<<"INSERT INTO "<<utility::get_table_name<T>()<<"(";
        std::vector<std::pair<std::string,std::string>> fieldInfo = utility::getStructFieldsInfo(struct_);

        for(size_t i = 0;i<fieldInfo.size();++i)
        {
            sql<<fieldInfo[i].first;
            if(i<fieldInfo.size()-1)
            {
                sql<<", ";
            }
        }   // for

        sql <<") VALUES (";

        // auto arg_list = {args...};
        // auto it = arg_list.begin();
        // for(size_t i = 0;i<fieldInfo.size();++i)
        // {
        //     sql<<"'"<<*it<<"'";
        //     ++it;
        //     if(i<fieldInfo.size()-1)
        //     {
        //         sql<<", ";
        //     }
        // }   // for

         std::vector<std::string> arg_list = {args...};
         for(size_t i = 0;i<arg_list.size();++i)
         {
            sql<<"'"<<arg_list[i]<<"'";
            if(i<arg_list.size()-1)
            {
                sql<<", ";
            }   // if
         }  // for

        sql<<");";

        return sql.str();

    }




};



#endif  // INSERT_ACTION_HPP