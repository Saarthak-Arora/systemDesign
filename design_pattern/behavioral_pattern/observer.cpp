#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Observer {
public:
    virtual void update(string msg) = 0;
};

class Subject {
    vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
    void notify(string msg) {
        for (auto obs : observers) {
            obs->update(msg);
        }
    }
};

class Subscriber : public Observer {
    string name;
public:
    Subscriber(string n) : name(n) {}
    void update(string msg) override {
        cout << name << " received: " << msg << "\n";
    }
};

int main() {
    Subject channel;

    Subscriber s1("Alice");
    Subscriber s2("Bob");

    channel.addObserver(&s1);
    channel.addObserver(&s2);

    channel.notify("New video uploaded!");
}
