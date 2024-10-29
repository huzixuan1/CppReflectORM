#ifndef UPDATE_ACTION_HPP
#define UPDATE_ACTION_HPP

#include "utility.hpp"
#include <sstream>
#include <boost/type_index.hpp>
using namespace std;

namespace updateAction
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

    // UPDATE table_name SET column1 = value1, column2 = value2 WHERE condition;
    template <typename T, typename... Args>
    std::string update(const T &struct_,const Condition &condition,Args... args)
    {
        std::ostringstream sql;
        sql << "UPDATE " << get_table_name<T>() << " SET ";
        std::vector<std::pair<std::string, std::string>> fieldInfo = utility::getStructFieldsInfo(struct_);

        std::string set_clause;
        auto arg_list = {args...};
        auto it_arg = arg_list.begin();
        for (const auto &filed : fieldInfo)
        {
            set_clause += filed.first + " = '" + *it_arg + "'";
            ++it_arg;
            if (it_arg != arg_list.end())
            {
                set_clause += ", ";

            } // if
        }

        sql << set_clause << " WHERE " << condition.to_sql()<<";";

        return sql.str();
    }

};

#endif // UPDATE_ACTION_HPP