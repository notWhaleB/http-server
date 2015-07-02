#include "main.h"
#include "server.h"

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

bool HttpServer::_echo_server_processor(int clientDesc) {
    char buf[BUF_SIZE];
    ssize_t clientReqSize = read(clientDesc, buf, BUF_SIZE);

#ifndef DISABLE_KILLER_FEATURE
    if (clientReqSize == 4 && strncmp(buf, "die", 3) == 0) {
        write(clientDesc, "O_O\n", 4);
        sleep(1);
        write(clientDesc, ";_;\n", 4);
        sleep(1);
        write(clientDesc, "x_x\n", 4);
        close(clientDesc);
        return false;
    }

#endif

    write(clientDesc, buf, clientReqSize);
    close(clientDesc);
    return true;
}

void HttpServer::_echo_server() {
    while (true) {
        int clientDescriptor = accept(_echo_serv_descriptor, nullptr, nullptr);
        if (!_echo_server_processor(clientDescriptor)) break;
    }
}

void HttpServer::start_echo_server(__uint32_t ip, __uint16_t port) {
    sockaddr_in addr;
    bzero(&addr, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_port = htons(port);

    _echo_serv_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    bindresvport(_echo_serv_descriptor, &addr);
    listen(_echo_serv_descriptor, SOMAXCONN);

    _echo_server();
    close(_echo_serv_descriptor);
}

HttpServer::HttpServer() {}
HttpServer::~HttpServer() {}
