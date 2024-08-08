#include <string>
#include <vector>
#include <iostream>

class QueryBuilder {
public:
    virtual void select() = 0;
    virtual void addColumn(const std::string& columnName) = 0;
    virtual void selectAllColumns() = 0;
    virtual void setTable(const std::string& tableName) = 0;
    virtual void addCondition(const std::string& condition) = 0;
    virtual std::string build() = 0;
};

class MySQLQueryBuilder : public QueryBuilder {
private:
    std::string sql;

public:
    void select() override {
        sql = "SELECT ";
    }

    void addColumn(const std::string& columnName) override {
        sql += columnName + ", ";
    }

    void selectAllColumns() override {
        sql += "* ";
    }

    void setTable(const std::string& tableName) override {
        sql += "FROM " + tableName + " ";
    }

    void addCondition(const std::string& condition) override {
        sql += "WHERE " + condition + " ";
    }

    std::string build() override {
        // Remove the trailing comma
        if (!sql.empty() && sql.back() == ' ')
            sql.pop_back();
        return sql + ";";
    }
};

class QueryDirector {
private:
    QueryBuilder* builder;

public:
    QueryDirector(QueryBuilder* builder) : builder(builder) {}

    // Construct with columns
    std::string construct(const std::vector<std::string>& columns, const std::string& tableName, const std::string& condition = "") {
        builder->select();
        for (const auto& column : columns) {
            builder->addColumn(column);
        }
        builder->setTable(tableName);
        if (!condition.empty()) {
            builder->addCondition(condition);
        }
        return builder->build();
    }

    // Construct without columns
    std::string construct(const std::string& tableName, const std::string& condition = "") {
        builder->select();
        builder->selectAllColumns();
        builder->setTable(tableName);
        if (!condition.empty()) {
            builder->addCondition(condition);
        }
        return builder->build();
    }
};

int main() {
    QueryBuilder* queryBuilder = new MySQLQueryBuilder();
    QueryDirector queryDirector(queryBuilder);

    std::vector<std::string> columns = {"id", "name"};
    std::cout << queryDirector.construct(columns, "example_table") << std::endl;

    std::cout << queryDirector.construct("example_table") << std::endl;

    std::cout << queryDirector.construct("example_table", "id = 1") << std::endl;

    delete queryBuilder;
    return 0;
}
