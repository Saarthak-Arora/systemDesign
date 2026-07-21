#include "AppendInFile.hpp"

AppendInFile::AppendInFile(string path) {
        filePath = path;
        logFile.open(filePath, ios::app);
        if (!logFile.is_open()) {
            cout << "Unable to open log file: " << filePath << endl;
        }
    }
void AppendInFile::appendLogMessage(int level, string message, time_t timestamp)  {
        lock_guard<mutex> lock(mtx);
        if (logFile.is_open()) {
            logFile << timestamp << " Level: " << level << ", Message: " << message << endl;
        } else {
            cout << "Unable to open log file: " << filePath << endl;
        }
    }
AppendInFile::~AppendInFile() {
        logFile.close();
}

