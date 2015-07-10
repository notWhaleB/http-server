#ifndef __HttpServer__server__
#define __HttpServer__server__

#include "main.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <string>
#include <thread>
#include <queue>
#include <atomic>
#include <poll.h>

const size_t BUF_SIZE = 1024;
const int POLL_TIMEOUT = 50;

class HttpServer {
private:
    std::queue<std::thread> _threadQueue; // TODO: make this on std::list and dynamically delete thread after closing in reason of lots of data collecting
    std::atomic_bool isStop;
    
    void _server_listener(int servDescriptor, std::function<void(int)> handler);

public:
    HttpServer();

    void start_server(uint32_t ip, uint16_t port, std::function<void(int)> handler);
    void stop_server();

    friend void echo_handler(int clientDescriptor);

    ~HttpServer();
};

void write_all(int clientDescriptor, const std::string &str);

#endif