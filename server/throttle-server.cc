#include<iostream>
#include<fstream>
#include<sstream>
#include<thread>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "throttle-server.h"
#include "reset-token-worker.h"
#include "process-request-worker.h"

ThrottleServer::ThrottleServer(const std::string& configfilePath) {
    
    if (!configfilePath.empty()) {
        std::ifstream config(configfilePath);
        if (config) {
            std::string configline;
            while (getline(config, configline)) {
                std::cout << configline << std::endl;
                size_t delimiterpos = configline.find(":");
                if ( delimiterpos!= std::string::npos) {
                    std::string token_str = configline.substr(delimiterpos + 1,
                                                configline.length());
                    std::stringstream ss(token_str);
                    int token_num = 0;
                    ss >> token_num;
                    // initialize both quota and current value maps
                    userTokenQuota.insert({configline.substr(0, delimiterpos), token_num});
                    userCurrentToken.insert({configline.substr(0, delimiterpos), token_num});
                }
            } // END while loop
        } else {
            std::cout << "Failed to open config file: [" << configfilePath << "], exiting.";
            exit(EXIT_FAILURE);
        }
        config.close();
    } else {
        std::cout << "config file path is empty, exiting." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ThrottleServer::run(int port) {
    // start a thread which will reset users current token value
    // to quota value
    std::thread resetQuotaWorker = std::thread(ResetTokenWorker(),
                                            std::ref(userTokenQuota),
                                            std::ref(userCurrentToken));
    // detach the thread to make it run as a daemon
    resetQuotaWorker.detach();

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    int server_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 == server_sock_fd) {
        std::cerr << "failed to create server socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // bind the socket and address
    if (bind(server_sock_fd, (struct sockaddr *)&address, addrlen) < 0) {
        std::cerr << "failed to bind server socket to port, exiting" << std::endl;
        exit(EXIT_FAILURE);
    }
    // start listening
    if (listen(server_sock_fd, MaxBacklog) < 0) {
        std::cerr << "failed to listen on the socket, exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    // accept connection indefinitely 
    while (true) {
        int new_socket = 0;
        if ((new_socket = accept(server_sock_fd,
                            (struct sockaddr*)&address,
                            (socklen_t*)&addrlen)) < 0) {
            std::cerr << "failed to accept connection on server socket, exiting" << std::endl;
            exit(EXIT_FAILURE);
        }
        // create a new thread to process each connection
        std::thread processRequestWorker(ProcessRequestWorker(),
                                    std::ref(new_socket),
                                    std::ref(userCurrentToken));
        if (processRequestWorker.joinable()) {
            processRequestWorker.join();
        }
    } // END while loop
}
