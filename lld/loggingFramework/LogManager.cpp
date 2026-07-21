#include "LogManager.hpp"

LogManager* LogManager::instance = nullptr;

LogManager::LogManager(LOG_LEVEL level)  {
    if(instance == nullptr) {
        lock_guard<mutex> lock(mtx);
        if(instance == nullptr) {
            logLevel = level;
            instance = this;
        }
    }else {
        cout<<"LogManager instance already exists"<<endl;
    }
    
    // Add default log locations (console and file)
    appendLocations.push_back(make_shared<AppendInConsole>());
    appendLocations.push_back(make_shared<AppendInFile>("log.txt"));
}

bool LogManager::shutdown(){
    if(instance != nullptr) {
        lock_guard<mutex> lock(mtx);
        if(instance != nullptr) {
            instance = nullptr;
            return true;
        }
    }
    return false;
}

LogManager::~LogManager() {
    shutdown();
}

// void LogManager::addLogLocation(Appendlocation* location) {
//         appendLocations.push_back(make_shared<Appendlocation>());
//     }

// void LogManager::removeLogLocation(Appendlocation* location) {
//         auto it = find(appendLocations.begin(), appendLocations.end(), location);
//         if(it != appendLocations.end()) {
//             appendLocations.erase(it);
//         }
//     }

