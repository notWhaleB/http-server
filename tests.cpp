#include "gtest.h"
#include "main.h"

std::string runPath;

TEST(HttpServerTest, StartStopTest) {
    HttpServer serv;
    serv.start_server(INADDR_ANY, 40001, http1_1_handler);
    serv.stop_server();
}

TEST(EchoServerTest, EchoTest) {
    HttpServer serv;

    serv.start_server(INADDR_ANY, 40001, echo_handler);

    sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr.sin_port = htons(40001);

    int clientDescriptor = wr_socket(AF_INET, SOCK_STREAM, 0);
    connect(clientDescriptor, (sockaddr*)(&addr), sizeof(addr));
    char *bufWrite = "ok";
    char bufRead[32];
    write(clientDescriptor, bufWrite, sizeof(bufWrite));
    read(clientDescriptor, bufRead, sizeof(bufRead));
    EXPECT_EQ(0, strncmp(bufWrite, bufRead, 2));
    close(clientDescriptor);

    serv.stop_server();
}

TEST(HttpServerTest, AddrReuseTest) {
    HttpServer serv;
    serv.start_server(INADDR_ANY, 40001, http1_1_handler);
    serv.stop_server();
    sleep(1);
    serv.start_server(INADDR_ANY, 40001, http1_1_handler);
    serv.stop_server();
}

int main(int argc, char **argv) {
    runPath = argv[0];
    while(runPath.back() != '/') {
        runPath.pop_back();
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}