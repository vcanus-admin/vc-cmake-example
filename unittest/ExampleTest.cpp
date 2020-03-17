//
// Created by SG Lee on 2019/10/23.
//
#include <gtest/gtest.h>
#include "../src/BoostLogger.h"

using namespace std;

class ExampleTest: public ::testing::Test {
protected:
    ExampleTest() {
    }
    virtual ~ExampleTest() {}
public:
    virtual void SetUp() {
        BoostLogger &logger = BoostLogger::get_instance();
        logger.set_filter(boost::log::trivial::info);
    }

    virtual void TearDown() {
    }
};

TEST_F(
        ExampleTest ,
        trueTest) {
    ASSERT_TRUE(true);
}

TEST_F(
        ExampleTest ,
        failTest) {
    ASSERT_TRUE(false);
}
