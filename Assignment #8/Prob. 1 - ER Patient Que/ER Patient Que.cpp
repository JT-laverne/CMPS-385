#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Patient {
    string id;
    string name;
    string condition;
    int severity;
    Patient* next;
};

Patient* head = nullptr;
int totalServed = 0;

// Function declarations
void loadPatients();
void savePatients();
void addPatient();
void displayQueue();
void servePatient();
void showSummary();

int main() {
    loadPatients();

    int choice;
    do {
        cout << "\n****** Welcome to ER Patient Queue Manager ******\n";
        cout << "1. Add New Patient\n2. Display Patient Queue\n3. Serve Next Patient\n4. View ER Summary\n5. Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: addPatient(); break;
        case 2: displayQueue(); break;
        case 3: servePatient(); break;
        case 4: showSummary(); break;
        case 5:
            savePatients();
            cout << "Patient queue saved to patients.txt. Stay safe!" << endl;
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}

// Load patients from file into linked list
void loadPatients() {
    ifstream fin("patients.txt");
    if (!fin) return;

    string id, name, condition;
    int severity;
    char comma;

    while (getline(fin, id, ',')) {
        getline(fin, name, ',');
        getline(fin, condition, ',');
        fin >> severity;
        fin.ignore(); // skip newline

        // create node
        Patient* newNode = new Patient{ id, name, condition, severity, nullptr };

        // append to end
        if (!head) head = newNode;
        else {
            Patient* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
    fin.close();
}

// Save linked list to patients.txt
void savePatients() {
    ofstream fout("patients.txt");

    Patient* temp = head;
    while (temp) {
        fout << temp->id << ","
            << temp->name << ","
            << temp->condition << ","
            << temp->severity << "\n";
        temp = temp->next;
    }
    fout.close();
}

// Add patient to end of linked list
void addPatient() {
    Patient* newNode = new Patient;

    cout << "Enter Patient ID: ";
    cin >> newNode->id;

    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, newNode->name);

    cout << "Enter condition: ";
    getline(cin, newNode->condition);

    cout << "Enter severity (1-5): ";
    cin >> newNode->severity;

    newNode->next = nullptr;

    if (head == nullptr)
        head = newNode;
    else {
        Patient* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    cout << "Patient added to the queue.\n";
}

// Display all patients
void displayQueue() {
    if (!head) {
        cout << "No patients in queue.\n";
        return;
    }

    cout << "\n=========== CURRENT QUEUE ===========\n";
    cout << left << setw(10) << "ID"
        << setw(20) << "Name"
        << setw(20) << "Condition"
        << "Severity\n";
    cout << "---------------------------------------------\n";

    Patient* temp = head;
    while (temp) {
        cout << left << setw(10) << temp->id
            << setw(20) << temp->name
            << setw(20) << temp->condition
            << temp->severity << "\n";
        temp = temp->next;
    }
}

// Serve next patient (remove head node)
void servePatient() {
    if (!head) {
        cout << "No patients in queue.\n";
        return;
    }

    Patient* temp = head;
    cout << "Serving Patient: " << temp->id << " - " << temp->name << "\n";

    head = head->next;
    delete temp;

    totalServed++;
}

// ER Summary
void showSummary() {
    int count = 0;
    int severitySum = 0;

    Patient* temp = head;
    while (temp) {
        count++;
        severitySum += temp->severity;
        temp = temp->next;
    }

    double avgSeverity = (count == 0) ? 0.0 : (double)severitySum / count;

    cout << "\n========== ER SUMMARY ==========\n";
    cout << "Total Patients Served: " << totalServed << "\n";
    cout << "Patients in Queue: " << count << "\n";
    cout << "Average Severity of Waiting Patients: "
        << fixed << setprecision(2) << avgSeverity << "\n";
    cout << "================================\n";
}
