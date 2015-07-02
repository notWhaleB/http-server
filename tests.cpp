#include "gtest.h"
#include "main.h"

TEST(BasicTest, ServerTest) {
    EXPECT_TRUE(socket(AF_INET, SOCK_STREAM, 0) > 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}