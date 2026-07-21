#include "Appendlocation.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>
using namespace std;


class AppendInFile : public Appendlocation
{
private:
    string filePath;
    ofstream logFile;
    mutex mtx;
public:
    AppendInFile(string path);
    void appendLogMessage(int level, string message, time_t timestamp) override;
    ~AppendInFile();
};
