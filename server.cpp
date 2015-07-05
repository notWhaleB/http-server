#include "main.h"
#include "server.h"

void handler::echo(HttpServer *ptr, int clientDescriptor) {
    char buf[BUF_SIZE];
    ssize_t clientRepSize = read(clientDescriptor, buf, BUF_SIZE);

    while (clientRepSize != 0) {
        clientRepSize -= write(clientDescriptor, buf, clientRepSize);
    }

    ptr->_e_close(clientDescriptor);
}


int HttpServer::_e_socket(int domain, int type, int protocol) {
    int desc = socket(domain, type, protocol);
    if (errno != 0) {
        perror("Socket error: ");
    }

    return desc;
};

void HttpServer::_e_bind(int desc, struct sockaddr_in *addr) {
    bindresvport(desc, addr);
    if (errno != 0) {
        perror("Bind error: ");
    }
}

void HttpServer::_e_listen(int desc, int backlog) {
    listen(desc, backlog);
    if (errno != 0) {
        perror("Listen error: ");
    }
}

int HttpServer::_e_accept(int desc, struct sockaddr *address, socklen_t *addressLen) {
    int clientDesc = accept(desc, address, addressLen);
    if (errno != 0) {
        perror("Client accept error: ");
    }

    return clientDesc;
}

void HttpServer::_e_close(int desc) {
    close(desc);
    if (errno != 0) {
        perror("Socket close error: ");
    }
}

void HttpServer::_server_listener(int servDescriptor, std::function<void(HttpServer *, int)> handler) {
    while (true) {
        int clientDescriptor = _e_accept(servDescriptor, nullptr, nullptr);
        _threadQueue.push(std::thread(handler, this, clientDescriptor));
    }
}

int HttpServer::start_server(uint32_t ip, uint16_t port, std::function<void(HttpServer *, int)> handler) {
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_port = htons(port);

    int servDescriptor = _e_socket(AF_INET, SOCK_STREAM, 0);
    _e_bind(servDescriptor, &addr);
    _e_listen(servDescriptor, SOMAXCONN);

    _threadQueue.push(std::thread(&HttpServer::_server_listener, this, servDescriptor, handler));

    return servDescriptor;
}

HttpServer::HttpServer() {}
HttpServer::~HttpServer() {
    while (_threadQueue.size() != 0) {
        _threadQueue.front().join();
        _threadQueue.pop();
    }
}
