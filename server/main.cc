#include <iostream>
#include<stdlib.h>

#include "throttle-server.h"

const int port = 8090;
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "USAGE: throttleserver <user-quota-config-file>" << std::endl;
        exit(EXIT_FAILURE);
    }
    const std::string& configfilepath = argv[1];

    // run throttling-server
    ThrottleServer server(configfilepath);
    std::cout << "INFO: starting throttling server...." << std::endl;
    server.run(port); 

    return 0;
}