#ifndef _RESET_TOKEN_WORKER_H_
#define _RESET_TOKEN_WORKER_H_

#include<map>

class ResetTokenWorker {
public:
    void operator()(const std::map<std::string, int>&,
                std::map<std::string, int>&);
};
#endif //_RESET_TOKEN_WORKER_H_