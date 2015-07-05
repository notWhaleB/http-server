#include "main.h"

int main(int argc, const char *argv[]) {
    HttpServer serv;
    serv.start_server(INADDR_ANY, 40000, handler::echo);

    return 0;
}
