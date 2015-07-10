#include "main.h"

std::string runPath;

int main(int argc, const char *argv[]) {
    runPath = argv[0];
    while(runPath.back() != '/') {
        runPath.pop_back();
    }

    HttpServer serv;
    std::cout << "Starting server..." << std::endl;
    serv.start_server(INADDR_ANY, 40000, http1_1_handler);
    std::cout << "Server started." << std::endl;

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "stop") {
            std::cout << "Stopping server..." << std::endl;
            serv.stop_server();
            std::cout << "Server stopped." << std::endl;
            return 0;
        } else {
            std::cout << cmd << ": command not found" << std::endl;
        }
    }

    return 0;
}
