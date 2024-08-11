#ifndef TABLE_BUILDER_TEST_HPP
#define TABLE_BUILDER_TEST_HPP

#include <gtest/gtest.h>
#include <createTable.hpp>

class TableBuildTest:public ::testing::Test{

public:
    void SetUp() override;

    void TearDown() override;

    std::vector<std::pair<std::string, std::string>> fields;

};



#endif //TABLE_BUILDER_TEST_HPP