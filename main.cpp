#include "main.h"

int main(int argc, const char *argv[]) {
    HttpServer serv;
    serv.start_server(INADDR_ANY, 40000, handler::echo);

    sleep(10);
    std::cout << "Stopping server..." << std::endl;
    serv.stop_server();

    return 0;
}
