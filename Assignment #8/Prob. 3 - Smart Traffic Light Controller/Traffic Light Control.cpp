#include <iostream>
#include <string>
using namespace std;

struct TrafficLight {
    int id;
    string roadName;
    string color;
    TrafficLight* next;
};

TrafficLight* head = nullptr;
TrafficLight* current = nullptr;

// Function declarations
void addLight();
void displaySequence();
void advanceLight();
void resetSystem();

// MAIN
int main() {
    int choice;
    do {
        cout << "\n****** Welcome to Smart Traffic Light Controller ******\n";
        cout << "1. Add Road and Light\n"
            << "2. Display Light Sequence\n"
            << "3. Advance to Next Light\n"
            << "4. Reset System\n"
            << "5. Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: addLight(); break;
        case 2: displaySequence(); break;
        case 3: advanceLight(); break;
        case 4: resetSystem(); break;
        case 5:
            cout << "Traffic system saved. Goodbye and drive safe!" << endl;
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

// Add a new traffic light
void addLight() {
    TrafficLight* newLight = new TrafficLight();

    cout << "Enter Road ID: ";
    cin >> newLight->id;
    cin.ignore();

    cout << "Enter Road Name: ";
    getline(cin, newLight->roadName);

    cout << "Enter Initial Light Color (Green/Yellow/Red): ";
    cin >> newLight->color;

    newLight->next = nullptr;

    if (head == nullptr) {
        head = newLight;
        newLight->next = newLight;
        current = head;
    }
    else {
        TrafficLight* temp = head;

        while (temp->next != head) {
            temp = temp->next;
        }

        temp->next = newLight;
        newLight->next = head;
    }

    cout << "Traffic light added for " << newLight->roadName << ".\n";
}

// Display the current sequence of traffic lights
void displaySequence() {
    if (head == nullptr) {
        cout << "No traffic lights in the system.\n";
        return;
    }

    cout << "\n========== TRAFFIC LIGHT SEQUENCE ==========\n";
    cout << "ID   Road Name          Light\n";
    cout << "----------------------------------------\n";

    TrafficLight* temp = head;

    do {
        cout << temp->id << "   "
            << temp->roadName << "   "
            << temp->color << endl;

        temp = temp->next;
    } while (temp != head);
}

// Advance to the next traffic light
void advanceLight() {
    if (head == nullptr) {
        cout << "No traffic lights to advance.\n";
        return;
    }

    if (current->next == current) {
        cout << current->roadName << " → Green (only road)\n";
        return;
    }

    TrafficLight* temp = head;

    do {
        temp->color = "Yellow";
        temp = temp->next;
    } while (temp != head);

    cout << current->roadName << " → Red\n";
    current->color = "Red";

    cout << current->next->roadName << " → Green\n";
    current->next->color = "Green";

    TrafficLight* other = current->next->next;
    while (other != current) {
        cout << other->roadName << " → Yellow\n";
        other = other->next;
    }

    current = current->next;
}

// Reset the traffic light system
void resetSystem() {
    if (head == nullptr) {
        cout << "System already empty.\n";
        return;
    }

    TrafficLight* temp = head->next;
    TrafficLight* nextNode;

    while (temp != head) {
        nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }

    delete head;

    head = nullptr;
    current = nullptr;

    cout << "System reset. All traffic lights cleared.\n";
}
