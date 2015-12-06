#include "wrappers.h"

int wr_socket(int domain, int type, int protocol) {
    int desc = socket(domain, type, protocol);
    if (desc == -1 && errno != 0) {
        perror("Socket error: ");
    }

    return desc;
};

void wr_bind(int desc, struct sockaddr_in *addr) {
    if (bindresvport(desc, addr) == -1 && errno != 0) {
        perror("Bind error: ");
    }
}

void wr_listen(int desc, int backlog) {
    if (listen(desc, backlog) == -1 && errno != 0) {
        perror("Listen error: ");
    }
}

int wr_accept(int desc, struct sockaddr *address, socklen_t *addressLen) {
    int clientDesc = accept(desc, address, addressLen);
    if (clientDesc == -1 && errno != 0) {
        perror("Client accept error: ");
    }

    return clientDesc;
}

void wr_close(int desc) {
    if (close(desc) == -1 && errno != 0) {
        perror("Socket close error: ");
    }
}

void wr_setsockopt(int socket, int level, int optionName, const void *optionValue, socklen_t optionLen) {
    if (setsockopt(socket, level, optionName, optionValue, optionLen) == -1 && errno != 0) {
        perror("Set socket error: ");
    }
}
