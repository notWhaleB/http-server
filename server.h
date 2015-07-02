#ifndef __HttpServer__server__
#define __HttpServer__server__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>
#include <string>
#include <thread>

const size_t BUF_SIZE = 1024;

class HttpServer {
private:
    int _echo_serv_descriptor;

    /* _e_func() -- error wrapper function for func() */
    int _e_socket(int domain, int type, int protocol);
    void _e_bind(int, struct sockaddr_in *);
    void _e_listen(int desc, int backlog);
    int _e_accept(int desc, struct sockaddr *, socklen_t *);
    void _e_close(int desc);
    void _echo_server();
    bool _echo_server_processor(int clientDesc);

public:
    HttpServer();

    void start_echo_server(const std::string &ip, __uint16_t port, size_t bufSize);
    void start_echo_server(__uint32_t ip, __uint16_t port);

    ~HttpServer();
};

#endif