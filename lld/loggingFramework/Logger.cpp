#include "Logger.hpp"


Logger::Logger(LOG_LEVEL x) : LogManager(x) {                      
    auto logManagerInstance = LogManager::getInstance();
    if(logManagerInstance == nullptr) {
        cout << "LogManager instance does not exist. start a new instance." << endl;
    }

    startWorkerThreads();

}

void Logger::log(int level, string message) {
    
    if(level < 0 || level > 3) {
        cout << "Invalid log level. Please provide a value between 0 and 3." << endl;
        return;
    }
    
    LOG_LEVEL currentLogLevel = getLogLevel();
    if(static_cast<int>(currentLogLevel) <= level) {
        lock_guard<mutex> lock(appendLogMutex);
        time_t now = time(nullptr);
        shared_ptr<LogMessage> logMsg = make_shared<LogMessage>(level, message, now);
        appendLogQueue.push(logMsg);
    }
    cv.notify_one();
    return;
}

void Logger::AppendLogMessage() {
    
    while (true) {
    shared_ptr<LogMessage> logMsg;

    {
        unique_lock<mutex> lock(appendLogMutex);

        cv.wait(lock, [this] {
    return shutdownFlag || !appendLogQueue.empty();
     });

    if (shutdownFlag && appendLogQueue.empty())
    return;

     while (!appendLogQueue.empty())
    {
        auto msg = appendLogQueue.front();
        appendLogQueue.pop();


        for (auto& appender : appendLocations)
            appender->appendLogMessage(msg->logLevel, msg->message , msg->timestamp);

    }
    }
    }


}

void Logger::startWorkerThreads() {
    for(int i = 0; i < numWorkerThreads; ++i) {
        threadPool.emplace_back(&Logger::AppendLogMessage, this);
    }
}

Logger::~Logger() {
    
    {
        lock_guard<mutex> lock(appendLogMutex);
        shutdownFlag = true;
    }

    cv.notify_all();

    for (auto& t : threadPool)
    {
        if (t.joinable())
            t.join();
    }
}