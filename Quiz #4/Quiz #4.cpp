#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// TEMPLATE STRUCT
template <typename T1, typename T2>
struct Appointment {
    T1 id;
    string name;
    string type;
    int timeUntil;
    T2 bill;
    string status;
};

// FUNCTION DECLARATIONS
template <typename T1, typename T2>
int loadAppointments(Appointment<T1, T2> appointments[]);

template <typename T1, typename T2>
void saveAppointments(Appointment<T1, T2> appointments[], int count);

template <typename T1, typename T2>
void addAppointment(Appointment<T1, T2> appointments[], int& count);

template <typename T1, typename T2>
void displayAppointments(Appointment<T1, T2> appointments[], int count);

template <typename T1, typename T2>
void markCompleted(Appointment<T1, T2> appointments[], int count);

template <typename T1, typename T2>
void appointmentSummary(Appointment<T1, T2> appointments[], int count);

// LOAD APPOINTMENTS FROM FILE
template <typename T1, typename T2>
int loadAppointments(Appointment<T1, T2> appointments[]) {
    ifstream file("appointments.txt");
    if (!file) return 0;

    int count = 0;
    string line;

    // Skip header line
    getline(file, line);

    while (getline(file, line)) {
        if (line == "") continue;

        Appointment<T1, T2> a;
        string temp;
        stringstream ss(line);

        getline(ss, a.id, ',');
        getline(ss, a.name, ',');
        getline(ss, a.type, ',');
        getline(ss, temp, ',');
        a.timeUntil = stoi(temp);
        getline(ss, temp, ',');
        a.bill = stof(temp);
        getline(ss, a.status, ',');

        appointments[count++] = a;
    }
    return count;
}

// SAVE APPOINTMENTS TO FILE
template <typename T1, typename T2>
void saveAppointments(Appointment<T1, T2> appointments[], int count) {
    ofstream file("appointments.txt");

    file << "ID,Name,Type,Time,Bill,Status\n";

    for (int i = 0; i < count; i++) {
        file << appointments[i].id << ","
            << appointments[i].name << ","
            << appointments[i].type << ","
            << appointments[i].timeUntil << ","
            << fixed << setprecision(2) << appointments[i].bill << ","
            << appointments[i].status << "\n";
    }
}

// ADD NEW APPOINTMENT
template <typename T1, typename T2>
void addAppointment(Appointment<T1, T2> appointments[], int& count) {
    if (count >= 100) {
        cout << "Maximum appointment limit reached.\n";
        return;
    }

    Appointment<T1, T2> a;

    cout << "Enter appointment ID: ";
    cin >> a.id;

    cin.ignore();
    cout << "Enter patient name: ";
    getline(cin, a.name);

    cout << "Enter appointment type: ";
    getline(cin, a.type);

    cout << "Enter time until appointment (hours): ";
    cin >> a.timeUntil;

    cout << "Enter estimated bill: ";
    cin >> a.bill;

    a.status = "Pending";

    appointments[count++] = a;

    cout << "Appointment added!\n";
}

// DISPLAY APPOINTMENTS
template <typename T1, typename T2>
void displayAppointments(Appointment<T1, T2> appointments[], int count) {
    cout << "\n=========== APPOINTMENTS ===========\n";
    cout << left << setw(10) << "ID"
        << setw(15) << "Name"
        << setw(12) << "Type"
        << setw(8) << "Time"
        << setw(10) << "Bill"
        << "Status\n";
    cout << "------------------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << appointments[i].id
            << setw(15) << appointments[i].name
            << setw(12) << appointments[i].type
            << setw(8) << appointments[i].timeUntil
            << "$" << setw(9) << fixed << setprecision(2) << appointments[i].bill
            << appointments[i].status << "\n";
    }
}

// MARK APPOINTMENT AS COMPLETED
template <typename T1, typename T2>
void markCompleted(Appointment<T1, T2> appointments[], int count) {
    T1 searchID;
    cout << "Enter appointment ID to mark as completed: ";
    cin >> searchID;

    for (int i = 0; i < count; i++) {
        if (appointments[i].id == searchID) {
            appointments[i].status = "Completed";
            cout << "Appointment " << searchID << " marked as Completed.\n";
            return;
        }
    }
    cout << "Appointment not found.\n";
}

// APPOINTMENT SUMMARY
template <typename T1, typename T2>
void appointmentSummary(Appointment<T1, T2> appointments[], int count) {
    int completed = 0;
    float earnings = 0;

    for (int i = 0; i < count; i++) {
        if (appointments[i].status == "Completed") {
            completed++;
            earnings += appointments[i].bill;
        }
    }

    cout << "\n======== APPOINTMENT SUMMARY ========\n";
    cout << "Total Appointments: " << count << "\n";
    cout << "Completed: " << completed << "\n";
    cout << "Pending: " << count - completed << "\n";
    cout << "Total Earnings: $" << fixed << setprecision(2) << earnings << "\n";
    cout << "=====================================\n";
}

// MAIN
int main() {
    Appointment<string, float> appointments[100];

    int count = loadAppointments(appointments);
    int choice;

    do {
        cout << "\n******* Welcome to Clinic Appointment Manager *******\n";
        cout << "1. Add New Appointment\n"
            << "2. Display All Appointments\n"
            << "3. Mark Appointment as Completed\n"
            << "4. View Appointment Summary\n"
            << "5. Exit\n→ ";

        cin >> choice;

        switch (choice) {
        case 1: addAppointment(appointments, count); break;
        case 2: displayAppointments(appointments, count); break;
        case 3: markCompleted(appointments, count); break;
        case 4: appointmentSummary(appointments, count); break;
        case 5:
            saveAppointments(appointments, count);
            cout << "Data saved to appointments.txt. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
