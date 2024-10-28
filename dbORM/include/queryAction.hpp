#ifndef QUERY_ACTION_HPP
#define QUERY_ACTION_HPP

#include <string>
#include <iostream>
#include <functional>
namespace selectAction
{
    template <typename L, typename R, typename Op>
    struct Expression
    {
        L left;
        R right;

        Expression(L l, R r) : left(l), right(r) {}

        std::string to_string() const
        {
            return left.to_string() + " " + Op::to_string() + " " + std::to_string(right);
        }
    };
    struct Greater
    {
        static std::string to_string()
        {
            return ">";
        }
    };

    template <typename L, typename R>
    auto operator>(L left, R right)
    {
        return Expression<L, R, Greater>(left, right);
    }
    template <typename T>
    struct Column
    {
        std::string name;

        Column(const std::string &name) : name(name) {}

        std::string to_string() const
        {
            return name;
        }
    };

    template <typename... Columns>
    std::string select(const std::string &table, Columns... cols)
    {
        std::string sql = "SELECT ";
        std::string columns = ((cols.to_string() + ", ") + ...);
        columns.pop_back();
        columns.pop_back();                // remove last comma and space
        sql += columns + " FROM " + table; // add from table
        return sql;
    }

    template <typename WhereExp>
    std::string where(WhereExp exp)
    {
        return " WHERE " + exp.to_string();
    }

    // order_by 函数
    template <typename OrderByExp>
    std::string order_by(OrderByExp exp)
    {
        return " ORDER BY " + exp.to_string();
    }


// test
// struct User {
//     int age;
//     std::string name;
// };

// int main() {

//     auto sql = select("users", Column<std::string>("name"), Column<int>("age")) +
//                where(Column<int>("age") > 18) +
//                order_by(Column<std::string>("name")) + ";";
//     std::cout << sql << std::endl;

//     return 0;
// }


};

#endif // QUERY_ACTION_HPP