#include <iostream>
#include<stdlib.h>
#include<signal.h>

#include "throttle-server.h"

const int port = 8090;

void signal_callback_handler(int signum) {
    // Terminate throttle server
    std::cout << std::endl << "terminating server... " << std::endl;
    exit(signum);
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "USAGE: throttleserver <user-quota-config-file>" << std::endl;
        exit(EXIT_FAILURE);
    }
    const std::string& configfilepath(std::move(argv[1]));

    // Register 'ctrl+c' signal and its signal handler
    signal(SIGINT, signal_callback_handler);

    // run throttling-server
    std::cout << "INFO: starting throttling server...." << std::endl;
    ThrottleServer::getInstance(configfilepath)->run(port);

    return EXIT_SUCCESS;
}
