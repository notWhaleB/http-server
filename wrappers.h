#ifndef __HttpServer__wrappers__
#define __HttpServer__wrappers__

#include "main.h"

int _e_socket(int domain, int type, int protocol);
void _e_bind(int, struct sockaddr_in *);
void _e_listen(int desc, int backlog);
int _e_accept(int desc, struct sockaddr *, socklen_t *);
void _e_close(int desc);

#endif
