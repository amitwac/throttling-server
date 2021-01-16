#ifndef _CLIENT_H_
#define _CLIENT_H_

#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>

const int MaxReqSize = 1024;

class Client {
private:
    std::string serverAddress;
    int port, sock;
    struct sockaddr_in sock_address;

    int createSocket();
public:
    Client(const std::string&, const int);
    int sendRequest(const std::string&, std::string&);
};

#endif // _CLIENT_H_