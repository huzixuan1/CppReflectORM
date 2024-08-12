#ifndef TABLE_BUILDER_HPP
#define TABLE_BUILDER_HPP

#include <memory>
#include <string>
#include <vector>
#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <boost/core/type_name.hpp>

// Abstract base class for building SQL tables

class TableBuilder {
public:
    virtual void setTableName(const std::string& tableName) = 0;
    virtual void addColumn(const std::string& columnName, const std::string& columnType) = 0;
    virtual void setPrimaryKey(const std::string& primaryKey) = 0;
    virtual void addForeignKey(const std::string& columnName, const std::string& foreignKey) = 0;
    virtual void addIndex(const std::string& columnName) = 0;
    virtual std::string build() = 0;
    virtual void reset() = 0;
    virtual ~TableBuilder() = default; // Virtual destructor for base class
};

// Concrete implementation of TableBuilder for MySQL
class MySQLTableBuilder : public TableBuilder {
private:
    std::string sql;

public:
    void setTableName(const std::string& tableName) override;
    void addColumn(const std::string& columnName, const std::string& columnType) override;
    void setPrimaryKey(const std::string& primaryKey) override;
    void addForeignKey(const std::string& columnName, const std::string& foreignKey) override;
    void addIndex(const std::string& columnName) override;
    std::string build() override;
    void reset() override;
};

// Director class for constructing SQL tables using a TableBuilder
class TableDirector {
private:
    std::shared_ptr<TableBuilder> builder;

public:
    TableDirector(std::shared_ptr<TableBuilder> builder);
    void construct(const std::string& tableName,
                   const std::vector<std::pair<std::string, std::string>>& columns,
                   const std::string& primaryKey = "",
                   const std::string& foreignKey = "",
                   const std::string& foreignKeyColumn = "");
};

// Function template to get field information from a struct
template<typename T>
std::vector<std::pair<std::string, std::string>> getStructFieldsInfo(const T& struct_t);


#endif  // TABLE_BUILDER_HPP