#include "server.h"

void HttpServer::_server_listener(int servDescriptor, std::function<void(int)> handler) {
    pollfd fd[1];
    fd[0].fd = servDescriptor;
    fd[0].events = POLL_IN;

    while (!isStop) {
        if (poll(fd, 1, POLL_TIMEOUT) == 1) {
            int clientDescriptor = wr_accept(servDescriptor, nullptr, nullptr);
            _threadQueue.push(std::thread(handler, clientDescriptor));
        }
    }

    wr_close(servDescriptor);
}

void HttpServer::start_server(uint32_t ip, uint16_t port, std::function<void(int)> handler) {
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_port = htons(port);

    int servDescriptor = wr_socket(AF_INET, SOCK_STREAM, 0);
    int optionValue = 1;
    wr_setsockopt(servDescriptor, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(optionValue));
    wr_bind(servDescriptor, &addr);
    wr_listen(servDescriptor, SOMAXCONN);

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

void write_all(int clientDescriptor, const std::string &str) {
    size_t last = 0;
    while (str.length() > last) {
        last += write(clientDescriptor, str.substr(last, str.length() - last).c_str(), str.length() - last);
    }
}


