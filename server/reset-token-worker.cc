#include<chrono>
#include<thread>
#include<iostream>

#include "reset-token-worker.h"

void ResetTokenWorker::operator()(const std::map<std::string, int>& quotaMap,
                                std::map<std::string, int>& currentValueMap) {
    while (true)
    {
        // at every tick of clock, reset user current token value to token quota limit
        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto itr = quotaMap.begin();
        while (itr != quotaMap.end()) {
            std::string user = itr->first;
            currentValueMap[user] = itr->second;
            itr++;
        }
    }
}