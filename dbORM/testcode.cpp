#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <typeindex>
#include <typeinfo>

// 表示用户结构体
struct User {
    int id;
    std::string name;
};

// 条件类
class Condition {
public:
    Condition(const std::string& field, const std::string& op, const std::string& value)
        : field(field), op(op), value(value) {}

    std::string to_sql() const {
        return field + " " + op + " '" + value + "'";
    }

private:
    std::string field;
    std::string op;
    std::string value;
};

// 表达式模板
template <typename L, typename R>
class Expression {
public:
    Expression(L left, R right) : left(left), right(right) {}

    std::string to_sql() const {
        return left + " < " + std::to_string(right);
    }

    // 提供 < 运算符重载
    friend bool operator<(const Expression& expr, const R& value) {
        return true; // 实际比较逻辑可以根据需要实现
    }

private:
    L left;
    R right;
};

// 存储类
class Storage {
public:
    // 查询方法
    template <typename T>
    std::vector<T> get_all(const Condition& condition) {
        std::string sql = "SELECT * FROM " + get_table_name<T>() + " WHERE " + condition.to_sql() + ";";
        std::cout << "Executing SQL: " << sql << std::endl;

        // 这里可以添加实际的数据库查询逻辑
        return {}; // 返回空结果以简化示例
    }

    template <typename T>
    std::string get_table_name() {
        return typeid(T).name(); // 使用 typeid 获取类型名
    }
};

// 辅助函数，创建条件对象
template <typename T>
Condition where(const Expression<std::string, int>& expr) {
    return Condition(expr.to_sql(), "<", "10");
}

// 用于构建列表达式
template <typename T>
Expression<std::string, int> c(int User::*member) {
    return Expression<std::string, int>("User.id", 0); // 使用成员指针构造表达式
}

// 重载运算符
template <typename L, typename R>
Expression<L, R> operator<(const L& left, const R& right) {
    return Expression<L, R>(left, right);
}

int main() {
    Storage storage;

    // 使用存储获取数据
    auto idLesserThan10 = storage.get_all<User>(where(c(&User::id) < 10));

    return 0;
}
