#include <iostream>
#include <string>
using namespace std;

class Task {
private:
    int id;
    string description;
    bool done;

public:
    //Constructors
    Task() {
        id = 0;
        description = "";
        done = false;
    }

    Task(int _id, string _desc) {
        id = _id;
        description = _desc;
        done = false;
    }

    //Getters
    int getId() const { return id; }
    string getDescription() const { return description; }
    bool isDone() const { return done; }

    //Setters
    void setId(int _id) { id = _id; }
    void setDescription(string _desc) { description = _desc; }
    void setDone(bool _done) { done = _done; }

    void toggle() {
        done = !done;
    }

    //Display full task
    void display() const {
        cout << "ID: " << id
            << " | \"" << description << "\" | Status: "
            << (done ? "Done" : "Pending") << endl;
    }
};

int main() {
    Task tasks[50];
    int taskCount = 0;
    int nextId = 1001;

    cout << "*********** Welcome to To-Do Manager ***********" << endl;

    int choice;

    do {
        cout << "1 - Add task" << endl;
        cout << "2 - Toggle task (by ID)" << endl;
        cout << "3 - List pending tasks" << endl;
        cout << "0 - Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            if (taskCount >= 50) {
                cout << "Task limit reached!" << endl;
                continue;
            }
            string desc;
            cout << "Enter description: ";
            getline(cin, desc);

            tasks[taskCount] = Task(nextId, desc);
            cout << "Task added! ID: " << nextId << endl;

            nextId++;
            taskCount++;
        }

        else if (choice == 2) {
            int id;
            cout << "Enter Task ID: ";
            cin >> id;

            bool found = false;
            for (int i = 0; i < taskCount; i++) {
                if (tasks[i].getId() == id) {
                    tasks[i].toggle();
                    cout << "Toggled task " << id << "." << endl;
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Task not found." << endl;
        }

        else if (choice == 3) {
            bool any = false;
            for (int i = 0; i < taskCount; i++) {
                if (!tasks[i].isDone()) {
                    tasks[i].display();
                    any = true;
                }
            }
            if (!any) {
                cout << "No pending tasks." << endl;
            }
        }

    } while (choice != 0);

    cout << "Goodbye!" << endl;
    return 0;
}
