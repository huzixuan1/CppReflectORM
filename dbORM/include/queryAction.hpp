#ifndef QUERY_ACTION_HPP
#define QUERY_ACTION_HPP

#include <sstream>
#include "utility.hpp"
namespace selectAction
{
    class Condition
    {
    private:
        std::string L;
        std::string op;
        std::string R;

    public:
        Condition(const std::string &L, const std::string &op, const std::string &R)
            : L(L), op(op), R(R) {}

        std::string to_sql() const
        {
            std::stringstream sql;
            sql << L << " " << op << " '" << R << "'";
            return sql.str();
        }
    };

    template <typename T>
    std::string get_table_name()
    {
        return boost::typeindex::type_id<T>().pretty_name();
    }

    // select age,name from tableName where age > 25;
    template <typename T, typename... Args>
    std::string create(const T &struct_,Condition &condition, Args... args)
    {
        std::ostringstream sql;
        sql << "SELECT ";

        auto arg_list = {args...};
        auto it = arg_list.begin();
        for (; it != arg_list.end(); ++it)
        {
            sql << *it;
            if (std::next(it) != arg_list.end())
            {
                sql << ", ";
            }
        }

        sql << " FROM " << utility::get_table_name<T>() << " WHERE " << condition.to_sql()<<";";

        return sql.str();
    }

};

#endif // QUERY_ACTION_HPP