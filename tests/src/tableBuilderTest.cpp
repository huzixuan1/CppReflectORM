#include "../include/tableBuilderTest.hpp"

void TableBuildTest::SetUp() {
    // builder = std::make_shared<MySQLTableBuilder>();
    // director = new TableDirector(builder);

    std::shared_ptr<TableBuilder> builder = std::make_shared<MySQLTableBuilder>();
    TableDirector director(builder);

        fields = {
        {"id", "INTEGER"},
        {"name", "TEXT"},
        {"salary", "REAL"}
    };

}

void TableBuildTest::TearDown() {
    // delete director;
}

TEST(SQLBuilderTest, ConstructsCorrectSQL) {

    struct response
    {
        int id;
        std::string name;
        double salary;
    };

    // std::shared_ptr<TableBuilder> builder = std::make_shared<MySQLTableBuilder>();
    // TableDirector director(builder);

    // std::string sql = buildSQLTable("response", fields, "id");

    director.construct("response", fields,"id");
    std::cout << builder->build() << std::endl;

    std::string expected_sql = "CREATE TABLE response (id INTEGER, name TEXT, salary REAL, PRIMARY KEY (id));";

    EXPECT_EQ(sql, expected_sql);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}