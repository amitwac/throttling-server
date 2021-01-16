#include<unistd.h>
#include<memory>

#include "process-request-worker.h"

void ProcessRequestWorker::operator()(const int& conn,
                                std::map<std::string, int>& userQuotaMap) {
    std::string respStr = "Deny";
    std::string reqStr = acceptRequest(conn);
    // request string will be "username"
    if (!reqStr.empty()) {
        // check if user is registered user or not
        auto itr = userQuotaMap.find(reqStr); 
        if (itr != userQuotaMap.end()) {
            // check if the user has valid token value left
            if (itr->second > 0) {
                // reduce the user quota by 1, and set resposne as 'Allow'
                --itr->second;
                respStr = "Allow";
            }
        } else {
            respStr = "Invalid user";
        }
    } else {
        respStr = "request string cannot be empty";
    }
    sendResponse(conn, respStr);
    // close the connection
    close(conn);
}

std::string ProcessRequestWorker::acceptRequest(const int& conn) {
    char buff[MaxReadBuffer] = {0};
    ssize_t valread = read(conn, buff, MaxReadBuffer);
    std::cout << "Read: " << valread << " bytes, value: ["<< buff << "] on the connection." << std::endl;
    return buff;
}

void ProcessRequestWorker::sendResponse(const int& conn, const std::string& respStr) {
    ssize_t bytesSent = write(conn, respStr.c_str(), respStr.length());
    std::cout<< "Sent bytes: [" << bytesSent << "]" << std::endl;
}
