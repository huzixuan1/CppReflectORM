#include <iostream>
#include "../include/createTable.hpp"
#include "../include/utility.hpp"

using namespace std;

// Implementations of MySQLTableBuilder methods
void MySQLTableBuilder::setTableName(const std::string& tableName) {
    sql += "CREATE TABLE " + tableName + " (";
}

void MySQLTableBuilder::addColumn(const std::string& columnName, const std::string& columnType) {
    sql += columnName + " " + columnType + ",";
}

void MySQLTableBuilder::setPrimaryKey(const std::string& primaryKey) {
    sql += "PRIMARY KEY (" + primaryKey + "),";
}

void MySQLTableBuilder::addForeignKey(const std::string& columnName, const std::string& foreignKey) {
    sql += "FOREIGN KEY (" + columnName + ") REFERENCES " + foreignKey + ",";
}

void MySQLTableBuilder::addIndex(const std::string& columnName) {
    sql += "INDEX (" + columnName + "),";
}

std::string MySQLTableBuilder::build() {
    sql.pop_back(); // Remove the last comma
    sql += ");";
    return sql;
}

void MySQLTableBuilder::reset() {
    sql = "";
}

// Implementations of TableDirector methods
// TableDirector::TableDirector(std::unique_ptr<TableBuilder> builder) : builder(std::move(builder)) {}
TableDirector::TableDirector(TableBuilder* builder) : builder(std::move(builder)) {}

void TableDirector::construct(const std::string& tableName,
                              const std::vector<std::pair<std::string, std::string>>& columns,
                              const std::string& primaryKey,
                              const std::string& foreignKey) {
    builder->reset();
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

struct response
{
    int id;
    std::string name;
    double salary;
};

int main()
{
    // std::unique_ptr<TableBuilder> builder;
    // TableDirector director(builder);

    TableBuilder* builder = new MySQLTableBuilder();
    TableDirector director(builder);

    // auto builder = make_unique<MySQLTableBuilder>();
    // TableDirector director(move(builder));

    response resp;
    std::vector<std::pair<std::string, std::string>> fields = utility::getStructFieldsInfo(resp);
    for(const auto& field:fields){
        std::cout<<"fileName:"<<field.first<<" ,SQL type:"<<field.second<<std::endl;
    }

    director.construct("response", fields,"id");
    std::cout << builder->build() << std::endl;

    delete builder;

    return 0;
}