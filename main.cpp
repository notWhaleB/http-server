#include "main.h"

int main(int argc, const char *argv[]) {
    HttpServer serv;
    serv.start_echo_server(INADDR_ANY, 40000);

    return 0;
}
