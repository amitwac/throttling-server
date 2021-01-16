#ifndef _THROTTLE_SERVER_H_
#define _THROTTLE_SERVER_H_

#include<iostream>
#include<map>

const int MaxBacklog = 10;

class ThrottleServer {
    std::map<std::string, int> userTokenQuota;
    std::map<std::string, int> userCurrentToken;

    ThrottleServer(const ThrottleServer&) {}

public:
    ThrottleServer(const std::string&);
    void run(int port);
};
#endif // _THROTTLE_SERVER_H_