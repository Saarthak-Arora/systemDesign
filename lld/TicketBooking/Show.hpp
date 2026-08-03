#pragma once
#include <string>
#include <iostream>
using namespace std;

class Show {
    public:
        const string show_id;
        const string showName;
        const double showPrice;
        Show(string show_id, string showName, double sp) : show_id(show_id), showName(showName), showPrice(sp) {}
        void getShowDetails() const {
            cout << "Show ID: " << show_id << endl;
            cout << "Show Name: " << showName << endl;
        }
};