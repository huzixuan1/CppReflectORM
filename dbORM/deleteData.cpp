
#include <string>
#include <iostream>
#include <sstream>
#include <boost/type_index.hpp>

using namespace std;

class Condition {
public:
    Condition(const std::string& field, const std::string& op, const std::string& value)
        : field(field), op(op), value(value) {}

    std::string to_sql() const {
        std::ostringstream sql;
        sql << field << " " << op << " '" << value << "'";
        return sql.str();
    }

private:
    std::string field; 
    std::string op;    // eg =, >, <, etc.
    std::string value; 
};

template<typename T>
std::string get_table_name() {
    return boost::typeindex::type_id<T>().pretty_name();
}

template <class T>
std::string remove(int id) {
    std::ostringstream sql;
    sql << "DELETE FROM " << get_table_name<T>() << " WHERE id = " << id;
    return sql.str();
}

template<typename T>
std::string remove_if(const Condition& condition) {
    std::ostringstream sql;
    sql << "DELETE FROM " << get_table_name<T>() << " WHERE " << condition.to_sql();
    return sql.str();
}

struct UserInfo {
    int age;
    std::string name;
};

int main() {
    auto table_name = get_table_name<UserInfo>();
    std::cout << table_name << std::endl;

    auto sql = remove<UserInfo>(1);
    std::cout << sql << std::endl;

    Condition condition("age", ">", "30");
    auto condition_sql = remove_if<UserInfo>(condition);
    std::cout << condition_sql << std::endl;

    return 0;
}

