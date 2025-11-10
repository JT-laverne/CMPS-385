#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//Struct definitions
struct Box {
    int id;
    string itemName;
    float weight;
    string destination;
};

//Stack Class 
class BoxStack {
private:
    static const int MAX = 100;
    Box stack[MAX];
    int top;

public:
    BoxStack() { top = -1; }

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX - 1; }

    void push(Box b) {
        if (isFull()) {
            cout << "Stack is full. Cannot add more boxes.\n";
            return;
        }
        stack[++top] = b;
        cout << "Box added to stack!\n";
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty. No boxes to dispatch.\n";
            return;
        }
        Box b = stack[top--];
        cout << "Top box dispatched:\n";
        cout << "ID: " << b.id << ", Item: " << b.itemName
            << ", Destination: " << b.destination << endl;
    }

    void peek() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }
        Box b = stack[top];
        cout << "Top Box: ID " << b.id << " - " << b.itemName << endl;
    }

    void displayStack() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "========= STACKED BOXES (Top to Bottom) =========\n";
        cout << left << setw(10) << "Box ID"
            << setw(15) << "Item"
            << setw(12) << "Weight(kg)"
            << setw(15) << "Destination" << endl;
        cout << "-----------------------------------------------\n";

        for (int i = top; i >= 0; i--) {
            cout << left << setw(10) << stack[i].id
                << setw(15) << stack[i].itemName
                << setw(12) << stack[i].weight
                << setw(15) << stack[i].destination << endl;
        }
    }

    void viewSummary() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }

        float totalWeight = 0.0;
        for (int i = 0; i <= top; i++) {
            totalWeight += stack[i].weight;
        }

        cout << "========== INVENTORY SUMMARY ==========\n";
        cout << "Total Boxes in Stack: " << (top + 1) << endl;
        cout << "Total Weight: " << totalWeight << " kg\n";
        cout << "Top Box: ID " << stack[top].id << " - " << stack[top].itemName << endl;
        cout << "=======================================\n";
    }

    void saveToFile() {
        ofstream fout("inventory.txt");
        if (!fout) {
            cout << "Error saving to file.\n";
            return;
        }
        for (int i = top; i >= 0; i--) {
            fout << stack[i].id << ","
                << stack[i].itemName << ","
                << stack[i].weight << ","
                << stack[i].destination << endl;
        }
        fout.close();
        cout << "Inventory saved to inventory.txt. Have a productive day!\n";
    }
};

// Main program
int main() {
    BoxStack warehouse;
    int choice;

    cout << "****** Welcome to Warehouse Inventory Stack Tracker ******\n";

    do {
        cout << "\nPlease choose one of the following operations:\n";
        cout << "1. Add Box to Stack\n";
        cout << "2. View Current Stack\n";
        cout << "3. Remove Top Box (Dispatch)\n";
        cout << "4. View Inventory Summary\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            if (warehouse.isFull()) {
                cout << "Stack is full. Cannot add more boxes.\n";
                break;
            }
            Box newBox;
            cout << "Enter Box ID: ";
            cin >> newBox.id;
            cin.ignore();
            cout << "Enter Item Name: ";
            getline(cin, newBox.itemName);
            cout << "Enter Weight (kg): ";
            cin >> newBox.weight;
            cin.ignore();
            cout << "Enter Destination: ";
            getline(cin, newBox.destination);
            warehouse.push(newBox);
            break;
        }
        case 2:
            warehouse.displayStack();
            break;
        case 3:
            warehouse.pop();
            break;
        case 4:
            warehouse.viewSummary();
            break;
        case 5:
            warehouse.saveToFile();
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
