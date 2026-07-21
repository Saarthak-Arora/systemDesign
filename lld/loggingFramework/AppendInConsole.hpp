#include "Appendlocation.hpp"
#include <iostream>
#include <string>

class AppendInConsole : public Appendlocation {
    private:
        std::mutex mtx;
    public:
        void appendLogMessage(int level,string message, time_t timestamp) override;
        ~AppendInConsole() {}

};

