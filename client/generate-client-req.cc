#include<unistd.h>


#include "generate-client-req.h"

Client::Client(const std::string& server, const int port)
    : serverAddress(std::move(server)), port(std::move(port)) {

}

int Client::createSocket() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Failed to create client socket." << std::endl;
        return EXIT_FAILURE;
    }
    sock_address.sin_family = AF_INET;
    sock_address.sin_port = htons(port);

    // convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, serverAddress.c_str(), &sock_address.sin_addr) <= 0) {
        std::cerr << "Invalid address or address is not supported." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
int Client::sendRequest(const std::string& user, std::string& resp) {
    // create client socket
    if (createSocket()) {
        return EXIT_FAILURE;
    }
    // connect to server
    if (connect(sock, (struct sockaddr*)&sock_address, sizeof(sock_address)) < 0) {
        std::cerr << "failed to connect to server: " << serverAddress << std::endl;
        return EXIT_FAILURE;
    }
    // send request
    char buff[MaxReqSize] = {0};
    send(sock, user.c_str(), user.length(), 0);

    // read response from server
    read(sock, buff, MaxReqSize);
    resp = std::string(buff);
 
    return EXIT_SUCCESS;
}