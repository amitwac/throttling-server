#ifndef _THROTTLE_SERVER_H_
#define _THROTTLE_SERVER_H_

#include<iostream>
#include<map>

const int MaxBacklog = 10;

// Singelton class
class ThrottleServer {
    std::map<std::string, int> userTokenQuota;
    std::map<std::string, int> userCurrentToken;
    static ThrottleServer* instance;

    ThrottleServer(const std::string&);
public:
    ThrottleServer(const ThrottleServer&) = delete;
    ThrottleServer& operator=(const ThrottleServer&) = delete;

    static ThrottleServer* getInstance(const std::string&);
    void run(int port);
};
#endif // _THROTTLE_SERVER_H_
