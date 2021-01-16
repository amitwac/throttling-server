#include<iostream>
#include<sstream>
#include<unistd.h>

#include "generate-client-req.h"

const int port = 8090;
const std::string throttleserver_addr = "127.0.0.1";

int main(int argc, char*argv[]) {
    if (argc < 3) {
        std::cerr << "USAGE: username request-count" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string username = argv[1];

    std::string countStr = argv[2];
    std::stringstream ss(countStr);
    int countNum = 0;
    ss >> countNum;

    // calculate sleep time to send countNum requests in 1 sec
    unsigned int sleepTime = 1000000 / countNum; // 1 second = 1000000 microseconds

    // instantiate client
    Client clientObj(throttleserver_addr, port);
    std::cout << "Sending Request: [" << username << "]" << ", " << countNum << " times." << std::endl;
    
    for (int index = 0; index < countNum; index++) {
 
        usleep(sleepTime);
 
        std::string serverResp;
        if (EXIT_FAILURE == clientObj.sendRequest(username, serverResp)) {
            std::cerr << "Failed to send request" << std::endl;
            break;
        } else {
            std::cout << "[" << username << "] " << serverResp << std::endl;
        }
    } // END for loop
    return 0;
}