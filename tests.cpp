#include "gtest.h"
#include "main.h"

TEST(BasicTest, ServerTest) {
    HttpServer serv;
    EXPECT_TRUE(serv.start_server(INADDR_ANY, 40001, handler::echo) > 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}