#include "reset-token-worker.h"
#include<chrono>
#include<thread>

void ResetTokenWorker::operator()(const std::map<std::string, int>& quotaMap,
                                std::map<std::string, int>& currentValueMap) {
    while (true)
    {
        // at every tick of clock, reset user current token value to token quota limit
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::map<std::string, int>::const_iterator citr = quotaMap.begin();
        while (citr != quotaMap.end()) {
            std::string user = citr->first;
            currentValueMap[user] = citr->second;
            citr++;
        }
    }
}