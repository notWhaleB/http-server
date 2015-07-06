#include "gtest.h"
#include "main.h"

TEST(HttpServerTest, StartStopTest) {
    HttpServer serv;
    serv.start_server(INADDR_ANY, 40001, handler::echo);
    serv.stop_server();
}

TEST(HttpServerTest, ReqestTest) {
    HttpServer serv;

    serv.start_server(INADDR_ANY, 40001, handler::echo);

    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(40001);

    int clientDescriptor = _e_socket(AF_INET, SOCK_STREAM, 0);
    connect(clientDescriptor, (sockaddr*)(&addr), sizeof(addr));
    char *bufWrite = "ok";
    char bufRead[32];
    write(clientDescriptor, bufWrite, sizeof(bufWrite));
    read(clientDescriptor, bufRead, sizeof(bufRead));
    EXPECT_EQ(0, strncmp(bufWrite, bufRead, 2));
    close(clientDescriptor);

    serv.stop_server();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}