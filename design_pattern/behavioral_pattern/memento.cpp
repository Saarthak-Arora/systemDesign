#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Memento {
    string state;
public:
    Memento(string s) : state(s) {}
    string getState() { return state; }
};

class Editor {
    string text;
public:
    void setText(string t) { text = t; }
    string getText() { return text; }

    Memento saveState() { return Memento(text); }
    void restoreState(Memento m) { text = m.getState(); }
};

class History {
    vector<Memento> states;
public:
    void push(Memento m) { states.push_back(m); }
    Memento pop() {
        Memento m = states.back();
        states.pop_back();
        return m;
    }
};

int main() {
    Editor editor;
    History history;

    editor.setText("Hello");
    history.push(editor.saveState());

    editor.setText("Hello World");
    history.push(editor.saveState());

    editor.setText("Hello World!!!");

    cout << "Current: " << editor.getText() << "\n";

    editor.restoreState(history.pop());
    cout << "After Undo: " << editor.getText() << "\n";

    editor.restoreState(history.pop());
    cout << "After Undo: " << editor.getText() << "\n";
}
