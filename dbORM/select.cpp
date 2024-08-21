
// #include <iostream>
// #include <string>
// #include <functional>

// // 表达式模板
// template<typename L, typename R, typename Op>
// struct Expression {
//     L left;
//     R right;
    
//     Expression(L l, R r) : left(l), right(r) {}
    
//     std::string to_string() const {
//         return left.to_string() + " " + Op::to_string() + " " + std::to_string(right);
//     }
// };

// // 自定义运算符类型
// struct Greater {
//     static std::string to_string() {
//         return ">";
//     }
// };

// // 运算符重载
// template<typename L, typename R>
// auto operator>(L left, R right) {
//     return Expression<L, R, Greater>(left, right);
// }

// // 列的表示
// template<typename T>
// struct Column {
//     std::string name;
    
//     Column(const std::string &name) : name(name) {}
    
//     std::string to_string() const {
//         return name;
//     }
// };

// // select 函数
// template<typename... Columns>
// std::string select(Columns... cols) {
//     std::string sql = "SELECT ";
//     std::string columns = ((cols.to_string() + ", ") + ...);
//     columns.pop_back();
//     columns.pop_back(); // remove last comma and space
//     sql += columns;
//     return sql;
// }

// // where 函数
// template<typename WhereExp>
// std::string where(WhereExp exp) {
//     return " WHERE " + exp.to_string();
// }

// // order_by 函数
// template<typename OrderByExp>
// std::string order_by(OrderByExp exp) {
//     return " ORDER BY " + exp.to_string();
// }

// // 示例结构体
// struct User {
//     int age;
//     std::string name;
// };

// int main() {
//     // 构造 SQL 语句
//     auto sql = select(Column<float>("name"), Column<float>("age")) +
//                where(Column<float>("age") > 18) +
//                order_by(Column<float>("name")) + ";";
    
//     // 输出 SQL 语句
//     std::cout << sql << std::endl;

//     return 0;
// }



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

template<typename L,typename R>
auto operator>(L left,R right){
    return Expression<L,R,Greater>(left,right);
}


template <typename T>
class Column
{
    public:
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
    std::string columns = ((cols.to_string() + ", ") + ...);
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

// 示例结构体
struct User {
    int age;
    std::string name;
};

int main() {
    // 构造 SQL 语句
    auto sql = select(Column<int>("name"), Column<int>("age")) +
               where(Column<int>("age") > 18) +
               order_by(Column<int>("name")) + ";";
    
    // 输出 SQL 语句
    std::cout << sql << std::endl;

    return 0;
}