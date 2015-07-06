#include "main.h"
#include "server.h"

void handler::echo(int clientDescriptor) {
    char buf[BUF_SIZE];
    pollfd fd[1];
    fd[0].fd = clientDescriptor;
    fd[0].events = POLL_IN;

    ssize_t clientRepSize = read(clientDescriptor, buf, BUF_SIZE);

    while (clientRepSize != 0) {
        clientRepSize -= write(clientDescriptor, buf, clientRepSize);
    }

    _e_close(clientDescriptor);
}

void HttpServer::_server_listener(int servDescriptor, std::function<void(int)> handler) {
    pollfd fd[1];
    fd[0].fd = servDescriptor;
    fd[0].events = POLL_IN;

    while (!isStop) {
        if (poll(fd, 1, POLL_TIMEOUT) == 1) {
            int clientDescriptor = _e_accept(servDescriptor, nullptr, nullptr);
            _threadQueue.push(std::thread(handler, clientDescriptor));
        }
    }

    close(servDescriptor);
}

void HttpServer::start_server(uint32_t ip, uint16_t port, std::function<void(int)> handler) {
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_port = htons(port);

    int servDescriptor = _e_socket(AF_INET, SOCK_STREAM, 0);
    _e_bind(servDescriptor, &addr);
    _e_listen(servDescriptor, SOMAXCONN);

    _threadQueue.push(std::thread(&HttpServer::_server_listener, this, servDescriptor, handler));
}

void HttpServer::stop_server() {
    isStop = true;
}

HttpServer::HttpServer() {
    isStop = false;
}

HttpServer::~HttpServer() {
    while (_threadQueue.size() != 0) {
        _threadQueue.front().join();
        _threadQueue.pop();
    }
}
