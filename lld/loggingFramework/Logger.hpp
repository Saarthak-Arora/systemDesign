#include <vector>
#include <queue>
#include "LogManager.hpp"
#include "LogMessage.hpp"
#include <memory>
#include <mutex>
#include <ctime>
#include <iostream>
#include <thread>
using namespace std;

class Logger : public LogManager {
private:    
    queue<shared_ptr<LogMessage>> appendLogQueue;
    void AppendLogMessage();

public:
    mutex logThreadsMutex;
    mutex appendLogMutex;
    vector<thread> threadPool;
   int  numWorkerThreads = 4; // You can adjust this number based on your requirements
   condition_variable cv;
   bool shutdownFlag = false;
    Logger(LOG_LEVEL x);
    void log(int level, string message) ;
    void setNumWorkerThreads(int numThreads) {
        numWorkerThreads = numThreads;
    }
    void startWorkerThreads();
    ~Logger();
};