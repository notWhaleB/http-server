#ifndef __HttpServer__server__
#define __HttpServer__server__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <string>
#include <thread>
#include <queue>

const size_t BUF_SIZE = 1024;

class HttpServer;

namespace handler {
    void echo(HttpServer *ptr, int clientDescriptor);
}

class HttpServer {
private:
    std::queue<std::thread> _threadQueue; // TODO: make this on std::list and dynamically delete thread after closing in reason of lots of data collecting

    /* _e_func() -- error wrapper function for func() */
    int _e_socket(int domain, int type, int protocol);
    void _e_bind(int, struct sockaddr_in *);
    void _e_listen(int desc, int backlog);
    int _e_accept(int desc, struct sockaddr *, socklen_t *);
    void _e_close(int desc);
    void _server_listener(int servDescriptor, std::function<void(HttpServer *, int)> handler);

public:
    HttpServer();

    int start_server(uint32_t ip, uint16_t port, std::function<void(HttpServer *, int)> handler);
    friend void handler::echo(HttpServer *ptr, int clientDescriptor);

    ~HttpServer();
};

#endif