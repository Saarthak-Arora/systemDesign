#include "AppendInConsole.hpp"

void AppendInConsole::appendLogMessage(int level, string message, time_t timestamp) {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << timestamp << " Level: " << level << ", Message: " << message << std::endl;
}
