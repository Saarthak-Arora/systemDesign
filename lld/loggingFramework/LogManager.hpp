#include <iostream>
#include <vector>
#include <memory>
#include "Appendlocation.hpp"
#include "AppendInConsole.hpp"
#include "AppendInFile.hpp"
using namespace std;

enum class LOG_LEVEL {
    INFO,
    DEBUG,
    WARN,
    ERR,
};
class LogManager {
    LOG_LEVEL logLevel;
    static LogManager* instance;
    
public:
mutex mtx;
vector<shared_ptr<Appendlocation>> appendLocations;
    LogManager() {
        logLevel = LOG_LEVEL::INFO; 
    }
    LogManager(LOG_LEVEL level);
    
    LOG_LEVEL getLogLevel() {
        return logLevel;
    }
    LOG_LEVEL setLogLevel(int level) {
        if(level < 0 || level > 3) {
            cout << "Invalid log level. Please provide a value between 0 and 3." << endl;
            return logLevel;
        }
        logLevel = static_cast<LOG_LEVEL>(level);
        return logLevel;
    }
    bool shutdown();

    LogManager* getInstance() {
        return instance;
    }

    void addLogLocation(Appendlocation* location);

    void removeLogLocation(Appendlocation* location);

    ~LogManager();

};