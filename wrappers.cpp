#include "wrappers.h"

int _e_socket(int domain, int type, int protocol) {
    int desc = socket(domain, type, protocol);
    if (errno != 0) {
        perror("Socket error: ");
    }

    return desc;
};

void _e_bind(int desc, struct sockaddr_in *addr) {
    bindresvport(desc, addr);
    if (errno != 0) {
        perror("Bind error: ");
    }
}

void _e_listen(int desc, int backlog) {
    listen(desc, backlog);
    if (errno != 0) {
        perror("Listen error: ");
    }
}

int _e_accept(int desc, struct sockaddr *address, socklen_t *addressLen) {
    int clientDesc = accept(desc, address, addressLen);
    if (errno != 0) {
        perror("Client accept error: ");
    }

    return clientDesc;
}

void _e_close(int desc) {
    close(desc);
    if (errno != 0) {
        perror("Socket close error: ");
    }
}
