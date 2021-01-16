#include<iostream>
#include<fstream>
#include<sstream>
#include<thread>
#include<unistd.h>

#include "throttle-server.h"
#include "reset-token-worker.h"

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
                    userTokenQuota.insert({configline.substr(0, delimiterpos), token_num});
                    userCurrentToken.insert({configline.substr(0, delimiterpos), token_num});
                }
            }
        } else {
            std::cout << "Failed to open config file: [" << configfilePath << "], exiting.";
            exit(1);
        }
        config.close();
    } else {
        std::cout << "config file path is empty, exiting." << std::endl;
        exit(1);
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
 
    return;
}