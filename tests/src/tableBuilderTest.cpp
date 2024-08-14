#include <string>
#include "utility.hpp"
#include "tableBuilderTest.hpp"

struct Department
{
    int pid;
    std::string name;
    int number;
};
struct Workers
{
    /* data */
    int id;
    std::string name;
    double salary;
    float high;
};

void TableBuildTest::SetUp()
{

    builder = std::make_shared<MySQLTableBuilder>();
    director = std::make_unique<TableDirector>(builder);
    
}

void TableBuildTest::TearDown()
{
    // delete director;
}

TableBuildTest::TableBuildTest() {}
TableBuildTest::~TableBuildTest() {}

/**
 * @brief Test the successful creation of a SQL table without defining primary key and foreign key.
 */

TEST_F(TableBuildTest, testCreateTableWithoutKey)
{

    Workers workers;
    fields = utility::getStructFieldsInfo(workers);

    director->construct("workers", fields, "id");
    auto actual = builder->build();
    auto expected = "CREATE TABLE workers (id INTEGER,name VARCHAR(255),salary REAL,high FLOAT,PRIMARY KEY (id));";

    ASSERT_EQ(actual, expected);
}

/**
 * @brief Test the successful creation of a SQL table with defining primary and foreign key.
 */

TEST_F(TableBuildTest,testCreateTableWithKey)
{
    Department department;
    fields = utility::getStructFieldsInfo(department);
    director->construct("department",fields,"name");

    Workers workers;
    fields = utility::getStructFieldsInfo(workers);
    director->construct("workers",fields,"id","name","department(name)");

    auto actual = builder->build();
    auto expected = "CREATE TABLE workers (id INTEGER,name VARCHAR(255),salary REAL,high FLOAT,PRIMARY KEY (id),FOREIGN KEY (name) REFERENCES department(name));";
    ASSERT_EQ(actual, expected);

}

// int main(int argc, char **argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }