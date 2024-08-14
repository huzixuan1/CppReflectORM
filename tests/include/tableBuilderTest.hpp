#ifndef TABLE_BUILDER_TEST_HPP
#define TABLE_BUILDER_TEST_HPP

#include <memory>
#include <gtest/gtest.h>
#include "createTable.hpp"

class TableBuildTest:public ::testing::Test{

public:

    virtual void SetUp() override;
    virtual void TearDown() override;

    TableBuildTest();
    ~TableBuildTest();

    std::shared_ptr<TableBuilder> builder;
    std::unique_ptr<TableDirector> director; 
    std::vector<std::pair<std::string, std::string>> fields;

};



#endif //TABLE_BUILDER_TEST_HPP