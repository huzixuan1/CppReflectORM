#ifndef INSERT_ACTION_HPP
#define INSERT_ACTION_HPP

#include "utility.hpp"
#include <sstream>
#include <vector>
#include <string>
#include <boost/pfr.hpp>

namespace insertAction
{
    // insert into tableName (id,weight,salary,userName) values (1,50,230,'tom');
    template <typename T>
    std::string insert(const T &struct_)
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

        // boost::pfr::for_each_field(struct_, [&sql, index = 0](const auto &field) mutable
        //                            {
        // using FieldType = std::decay_t<decltype(field)>;
        // if constexpr (std::is_integral<FieldType>::value || std::is_floating_point<FieldType>::value) {
        //     sql << field;
        // } else {
        //     sql << "'" << field << "'";
        // }

        // if (++index < boost::pfr::tuple_size<T>())
        //     sql << ", "; });

        // sql << ");";
        // return sql.str();

        boost::pfr::for_each_field(struct_, [&sql, index = 0](const auto &field) mutable
                                   {
            using FieldType = std::decay_t<decltype(field)>;

            if constexpr (std::is_same_v<FieldType, std::string>)
            {
                sql << "'" << field << "'";  // string
            }
            else
            {
                sql << field;  // no-string
            }

            if (++index < boost::pfr::tuple_size<T>())
                sql << ", "; });

        sql << ");";
        return sql.str();
    }

}

#endif // INSERT_ACTION_HPP
