#ifndef QUERY_ACTION_HPP
#define QUERY_ACTION_HPP

#include <string>
#include <iostream>
#include <functional>

template <typename L, typename R, typename OP>
class Expression
{
public:
    L left;
    R right;
    Expression(L l, R r) : left(l), right(r) {}
    Expression() = delete;

    std::string to_string() const
    {
        return left.to_string() + " " + OP::to_string() + " " + std::to_string(right);
    }
};

class Greater
{
public:
    static std::string to_string()
    {
        return ">";
    }
};

template <typename T>
class Column
{
    std::string name;
    Column(const std::string &name) : name(name) {}
    std::string to_string() const
    {
        return name;
    }
};

template <typename... Columns>
std::string select(Columns... cols)
{
    std::string sql = "SELECT";
    std::string columns = ((cols.to_string() + ', ') + ...);
    columns.pop_back();
    columns.pop_back();
    sql += columns;
    return sql;
}

template <typename WhereExp>
std::string where(WhereExp exp)
{
    return " WHERE " + exp.to_string();
}

template <typename OrderByExp>
std::string order_by(OrderByExp exp)
{
    return " ORDER BY " + exp.to_string();
}

#endif // QUERY_ACTION_HPP