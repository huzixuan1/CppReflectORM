#ifndef INSERT_ACTION_HPP
#define INSERT_ACTION_HPP

#include "utility.hpp"
#include <sstream>
#include <vector>
#include <string>
#include <boost/pfr.hpp> 

namespace insertAction
{
    // insert into tableName (id,weight,salary,userName) values (1,50,230,tom);
    template<typename T>
    std::string insert(const T& struct_)
    {
        std::ostringstream sql;
        sql << "INSERT INTO " << utility::get_table_name<T>() << " (";

        std::vector<std::pair<std::string, std::string>> fieldInfo = utility::getStructFieldsInfo(struct_);

        for (size_t i = 0; i < fieldInfo.size(); ++i)
        {
            sql << fieldInfo[i].first;
            if (i < fieldInfo.size() - 1)
            {
                sql << ", ";
            }
        }
        sql << ") VALUES (";

        boost::pfr::for_each_field(struct_, [&sql, index = 0](const auto &field) mutable {
            if constexpr (std::is_same_v<std::decay_t<decltype(field)>, std::string>)
                sql << "'" << field << "'";
            else
                sql << "'" << std::to_string(field) << "'";

            if (++index < boost::pfr::tuple_size<T>())
                sql << ", ";
        });

        sql << ");";
        return sql.str();
    }
}

#endif // INSERT_ACTION_HPP
