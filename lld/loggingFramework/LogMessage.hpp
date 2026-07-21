#include<ctime>
#include<string>
using namespace std;

class LogMessage{

public:
    int logLevel;
    string message;
    time_t timestamp;
    LogMessage(int logLevel,string  msg, time_t time){
        this->logLevel = logLevel;
        message = msg;
        timestamp = time;
    }
};