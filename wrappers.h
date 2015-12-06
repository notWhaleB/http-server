#ifndef __HttpServer__wrappers__
#define __HttpServer__wrappers__

#include "main.h"
#include <sys/socket.h>

int wr_socket(int domain, int type, int protocol);
void wr_bind(int, struct sockaddr_in *);
void wr_listen(int desc, int backlog);
int wr_accept(int desc, struct sockaddr *, socklen_t *);
void wr_close(int desc);
void wr_setsockopt(int socket, int level, int optionName, const void *optionValue, socklen_t optionLen);

#endif
