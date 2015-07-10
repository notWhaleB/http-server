#include "echo.h"

void echo_handler(int clientDescriptor) {
    char buf[BUF_SIZE];

    ssize_t clientRepSize = read(clientDescriptor, buf, BUF_SIZE);
    std::string reply;
    for (ssize_t i = 0; i != clientRepSize; ++i) {
        reply += buf[i];
    }
    write_all(clientDescriptor, reply);

    wr_close(clientDescriptor);
}

