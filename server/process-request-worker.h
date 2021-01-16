#ifndef _PROCESS_REQUEST_WORKER_H_
#define _PROCESS_REQUEST_WORKER_H_

#include<iostream>
#include<map>

const int MaxReadBuffer = 1024;
class ProcessRequestWorker {
private:
    std::string acceptRequest(const int&);
    void sendResponse(const int&, const std::string&);
public:
  void operator()(const int&, std::map<std::string, int>&);
};

#endif //_PROCESS_REQUEST_WORKER_H_