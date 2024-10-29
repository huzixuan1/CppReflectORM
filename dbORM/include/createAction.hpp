#ifndef CREATE_ACTION_HPP
#define CREATE_ACTION_HPP

#include "utility.hpp"

namespace createAction
{


    // 1.create tableName (student_id INT,name VARCHAR(50),age INT);
    template<typename T,typename...Args>
    std::string createTable(const T& struct_,Args...args)
    {
        
    }



};


#endif  // CREATE_ACTION_HPP