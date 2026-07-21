#include "Logger.hpp"
#include <iostream>
using namespace std;

int main(){
    Logger logger(LOG_LEVEL::INFO);
    logger.log(0, "This is an info message.");
    logger.log(1, "This is a debug message.");
    logger.log(2, "This is a warning message.");
    logger.log(3, "This is an error message.");

    for(int i = 0; i < 10; ++i) {
        logger.log(0, "Logging from main thread.");
    }

    vector<thread> threads;
    for(int i = 0; i < 5; ++i) {
        threads.emplace_back([&logger, i]() {
            for(int j = 0; j < 5; ++j) {
                logger.log(1, ("Logging from thread " + to_string(i)).c_str());
            }
        });
        
    }


    for(auto& t : threads) {
        t.join();
    }


    return 0;
} 