#include <string>
#include <vector>
#include <iostream>
#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <boost/core/type_name.hpp>

class TableBuilder {
public:
    virtual void setTableName(const std::string& tableName) = 0;
    virtual void addColumn(const std::string& columnName, const std::string& columnType) = 0;
    virtual void setPrimaryKey(const std::string& primaryKey) = 0;
    virtual void addForeignKey(const std::string& columnName, const std::string& foreignKey) = 0;
    virtual void addIndex(const std::string& columnName) = 0;
    virtual std::string build() = 0;
    virtual void reset() = 0;
};

class MySQLTableBuilder : public TableBuilder {
private:
    std::string sql;

public:
    void setTableName(const std::string& tableName) override {
        sql += "CREATE TABLE " + tableName + " (";
    }

    void addColumn(const std::string& columnName, const std::string& columnType) override {
        sql += columnName + " " + columnType + ",";
    }

    void setPrimaryKey(const std::string& primaryKey) override {
        sql += "PRIMARY KEY (" + primaryKey + "),";
    }

    void addForeignKey(const std::string& columnName, const std::string& foreignKey) override {
        sql += "FOREIGN KEY (" + columnName + ") REFERENCES " + foreignKey + ",";
    }

    void addIndex(const std::string& columnName) override {
        sql += "INDEX (" + columnName + "),";
    }

    std::string build() override {
        sql.pop_back(); // Remove the last comma
        sql += ");";
        return sql;
    }

    void reset() override {
        sql = "";
    }
};

class TableDirector {
private:
    TableBuilder* builder;

public:
    TableDirector(TableBuilder* builder) : builder(builder) {}

    void construct(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& columns, const std::string& primaryKey = "", const std::string& foreignKey = "") {
        builder->reset(); // Reset the builder's state
        builder->setTableName(tableName);
        for (const auto& column : columns) {
            builder->addColumn(column.first, column.second);
        }
        if (!primaryKey.empty()) {
            builder->setPrimaryKey(primaryKey);
        }
        if (!foreignKey.empty()) {
            builder->addForeignKey("column_name", foreignKey);
        }
    }
};

template<typename T>
std::vector<std::pair<std::string, std::string>> getStructFieldsInfo(const T& struct_t) {
    std::vector<std::pair<std::string, std::string>> fieldsInfo;

    constexpr auto names = boost::pfr::names_as_array<T>();
    boost::pfr::for_each_field(
        struct_t, [&fieldsInfo, &names](const auto& field, std::size_t idx) {
            std::string typeName = boost::core::type_name<std::decay_t<decltype(field)>>();
            std::string fieldName = std::string(names[idx]);
            fieldsInfo.emplace_back(fieldName, typeName);
        });

    return fieldsInfo;
}

struct testdb
{
    int testId;
};

struct response
{
    int id;
    double salary;
    std::string words;
    testdb abc;
};

int main() {
    TableBuilder* builder = new MySQLTableBuilder();
    TableDirector director(builder);

    std::vector<std::pair<std::string, std::string>> columns = {{"id", "INT"}, {"name", "VARCHAR(255)"}};

    director.construct("example_table", columns);
    std::cout << builder->build() << std::endl;

    director.construct("example_table", columns,"id");
    std::cout << builder->build() << std::endl;

    response resp;
    std::vector<std::pair<std::string, std::string>> fields = getStructFieldsInfo(resp);
    director.construct("response", fields,"id");
    std::cout << builder->build() << std::endl;

    delete builder;
    
    return 0;
}