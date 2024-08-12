#include <iostream>
#include "../include/utility.hpp"
#include "../include/createTable.hpp"

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
TableDirector::TableDirector(std::shared_ptr<TableBuilder> builder) : builder(std::move(builder)) {}

void TableDirector::construct(const std::string& tableName,
                              const std::vector<std::pair<std::string, std::string>>& columns,
                              const std::string& primaryKey,
                              const std::string& foreignKey,
                              const std::string& foreignKeyColumn) {
    builder->reset();
    builder->setTableName(tableName);
    for (const auto& column : columns) {
        builder->addColumn(column.first, column.second);
    }
    if (!primaryKey.empty()) {
        builder->setPrimaryKey(primaryKey);
    }
    if (!foreignKey.empty()) {
        builder->addForeignKey(foreignKey, foreignKeyColumn);
    }
}

struct response
{
    int id;
    std::string name;
    double salary;
};

struct department
{
    int pid;
    std::string name;
    int number;
};

int main()
{
    std::shared_ptr<TableBuilder> builder = std::make_shared<MySQLTableBuilder>();
    TableDirector director(builder);

    department depart;
    std::vector<std::pair<std::string, std::string>> fieldsDepart = utility::getStructFieldsInfo(depart);

    director.construct("department", fieldsDepart,"name");
    std::cout << builder->build() << std::endl;

    response resp;
    std::vector<std::pair<std::string, std::string>> fields = utility::getStructFieldsInfo(resp);

    director.construct("response", fields,"id","name","department(name)");
    std::cout << builder->build() << std::endl;

    return 0;
}