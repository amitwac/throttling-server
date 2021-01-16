#include <iostream>
#include "throttle-server.h"

const int port = 8080;
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "USAGE: throttleserver <user-quota-config-file>" << std::endl;
        exit(1);
    }
    const std::string& configfilepath = argv[1];

    // run throttling-server
    ThrottleServer server(configfilepath);
    server.run(port); 

    return 0;
}