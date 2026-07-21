#pragma once
#include <ctime>
#include <string>
using std::string;

class Appendlocation {
public:
    Appendlocation() = default;
    virtual void appendLogMessage(int level, string message, time_t timestamp){}
    //bool operator==(const Appendlocation&) const;
    virtual ~Appendlocation() = default;
};