#include <string>
#include "utility.hpp"
#include "tableBuilderTest.hpp"

void TableBuildTest::SetUp()
{

    builder = std::make_shared<MySQLTableBuilder>();
    director = std::make_unique<TableDirector>(builder);

    struct tableBuilderTest
    {
        /* data */
        int id;
        std::string name;
        double salary;
        float high;
    };

    tableBuilderTest tableBuild;
    fields = utility::getStructFieldsInfo(tableBuild);
    
}

void TableBuildTest::TearDown()
{
    // delete director;
}

TableBuildTest::TableBuildTest() {}
TableBuildTest::~TableBuildTest() {}

TEST_F(TableBuildTest, ConstructsCorrectSQL)
{
    director->construct("response", fields, "id");
    auto sql = builder->build();
    // std::cout<<"sql:"<<sql<<std::endl;
    std::cout << builder->build() << std::endl;
    std::string expected_sql = "CREATE TABLE response (id INTEGER,name VARCHAR(255),salary REAL,high FLOAT,PRIMARY KEY (id));";

    EXPECT_EQ(sql, expected_sql);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}