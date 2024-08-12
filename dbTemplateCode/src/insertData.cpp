// #include <iostream>
// #include <string>
// #include <vector>
// #include <boost/pfr/core.hpp>
// #include <boost/core/type_name.hpp>
// #include <stdexcept>

// // 插入构建器接口
// class InsertBuilder {
// public:
//     virtual void setTableName(const std::string& tableName) = 0;
//     virtual void addColumn(const std::string& columnName) = 0;
//     virtual void addValue(const std::string& value) = 0;
//     virtual std::string build() = 0;
//     virtual void reset() = 0;
// };

// // MySQL 插入语句构建器实现
// class MySQLInsertBuilder : public InsertBuilder {
// private:
//     std::string sql;
//     bool firstColumn = true;
//     bool firstValue = true;

// public:
//     void setTableName(const std::string& tableName) override {
//         sql += "INSERT INTO " + tableName + " (";
//     }

//     void addColumn(const std::string& columnName) override {
//         if (!firstColumn) {
//             sql += ", ";
//         }
//         sql += columnName;
//         firstColumn = false;
//     }

//     void addValue(const std::string& value) override {
//         if (!firstValue) {
//             sql += ", ";
//         }
//         sql += value;
//         firstValue = false;
//     }

//     std::string build() override {
//         sql += ") VALUES (";
//         sql += ")"; // 这里要确保在 VALUES 后拼接的值是正确的
//         return sql;
//     }

//     void reset() override {
//         sql = "";
//         firstColumn = true;
//         firstValue = true;
//     }
// };

// // 获取结构体字段信息并生成插入语句
// template<typename T>
// void constructInsertStatement(InsertBuilder& builder, const T& obj) {
//     builder.reset();
    
//     std::string tableName = boost::core::type_name<T>();
//     if (tableName.empty()) {
//         throw std::runtime_error("Failed to get type name for table");
//     }
//     builder.setTableName(tableName);

//     std::vector<std::string> fieldNames = {"id", "name", "salary"}; // 替换为实际字段名称
//     if (fieldNames.empty()) {
//         throw std::runtime_error("Field names array is empty");
//     }

//     constexpr std::size_t fieldCount = boost::pfr::tuple_size<T>::value;
//     if (fieldNames.size() != fieldCount) {
//         throw std::runtime_error("Mismatch between field names count and field count in structure");
//     }

//     // 构建列名和对应的值
//     std::vector<std::string> values;
//     boost::pfr::for_each_field(obj, [&builder, &fieldNames, &values](const auto& field, std::size_t idx) {
//         if (idx >= fieldNames.size()) {
//             throw std::runtime_error("Field index out of bounds");
//         }

//         std::string columnName = fieldNames[idx];
//         if (columnName.empty()) {
//             throw std::runtime_error("Field name is empty");
//         }
//         builder.addColumn(columnName);

//         // Format the value properly
//         std::string value;
//         if constexpr (std::is_same_v<std::decay_t<decltype(field)>, std::string>) {
//             value = "'" + field + "'";
//         } else if constexpr (std::is_arithmetic_v<std::decay_t<decltype(field)>>) {
//             value = std::to_string(field);
//         } else {
//             value = "'" + boost::core::type_name<std::decay_t<decltype(field)>>() + "'";
//         }
//         values.push_back(value);
//     });

//     // 在 build 方法中拼接 VALUES 部分
//     std::string finalSql = builder.build();
//     finalSql.replace(finalSql.find("VALUES ()"), 8, "(" + boost::algorithm::join(values, ", ") + ")");
//     std::cout << finalSql << std::endl;
// }

// // 示例结构体
// struct User {
//     int id;
//     std::string name;
//     double salary;
// };

// // 主函数
// int main() {
//     try {
//         MySQLInsertBuilder insertBuilder;

//         User user{1, "Alice", 50000.0};
//         constructInsertStatement(insertBuilder, user);
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }

//     return 0;
// }



#include <string>
#include <vector>
#include <iostream>
#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <boost/core/type_name.hpp>
#include <sstream>
#include <type_traits>
#include <optional>

// Generic conversion function
template<typename T>
std::string convertToString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Specialization for std::string
template<>
std::string convertToString(const std::string& value) {
    return value;
}

// Specialization for std::optional
template<typename T>
std::string convertToString(const std::optional<T>& opt) {
    if (opt.has_value()) {
        return convertToString(opt.value());
    } else {
        return "NULL"; // Or any other representation for null values
    }
}

// Retrieve struct field names and values
template<typename T>
std::vector<std::pair<std::string, std::string>> getStructFieldsInfo(const T& struct_t) {
    std::vector<std::pair<std::string, std::string>> fieldsInfo;
    constexpr auto names = boost::pfr::names_as_array<T>();

    boost::pfr::for_each_field(struct_t, [&fieldsInfo, &names](const auto& field, std::size_t idx) {
        fieldsInfo.emplace_back(std::string(names[idx]), convertToString(field));
    });

    return fieldsInfo;
}

// Type trait to check if a struct has a primary key
template<typename T>
struct has_primary_key {
    static constexpr bool value = false;
};

template<>
struct has_primary_key<struct User> {
    static constexpr bool value = true;
};

// Base template for SQL generation
template<typename T>
std::string generateSQL(const T& struct_t, const std::string& tableName,
                        typename std::enable_if<!has_primary_key<T>::value, int>::type = 0) {
    auto fields = getStructFieldsInfo(struct_t);
    std::ostringstream sql, values;

    sql << "INSERT INTO " << tableName << " (";
    values << "VALUES (";

    for (const auto& field : fields) {
        sql << field.first << ",";
        values << "'" << field.second << "',";
    }

    // Remove the trailing commas
    sql.seekp(-1, std::ios_base::end);
    values.seekp(-1, std::ios_base::end);

    sql << ") ";
    values << ");";

    sql << values.str();
    return sql.str();
}

// Template specialization for tables with primary keys
template<typename T>
std::string generateSQL(const T& struct_t, const std::string& tableName,
                        typename std::enable_if<has_primary_key<T>::value, int>::type = 0) {
    auto fields = getStructFieldsInfo(struct_t);
    std::ostringstream sql, values;

    sql << "INSERT INTO " << tableName << " (";
    values << "VALUES (";

    for (const auto& field : fields) {
        // Skip the primary key in the insert statement if not provided
        if (field.first != "id") { // Assuming "id" is the primary key
            sql << field.first << ",";
            values << "'" << field.second << "',";
        }
    }

    // Remove the trailing commas
    sql.seekp(-1, std::ios_base::end);
    values.seekp(-1, std::ios_base::end);

    sql << ") ";
    values << ");";

    sql << values.str();
    return sql.str();
}

// Struct definitions
struct User {
    int id;
    std::string name;
    int age;
    std::optional<int> address_id;  // Foreign key
};

struct Product {
    int id;
    std::string name;
    double price;
    std::optional<int> supplier_id; // Foreign key
};

int main() {
    User user{1, "John Doe", 30, 2};
    Product product{1, "Laptop", 999.99, std::nullopt};

    // Example usage of the function template specializations
    std::cout << generateSQL(user, "User") << std::endl;
    std::cout << generateSQL(product, "Product") << std::endl;

    return 0;
}
