#include <iostream>
#include <string>
#include <cstdlib>  
#include <ctime>    

using namespace std;

//Struct Definitions
struct Date {
    int day;
    int month;
    int year;
};

struct Appointment {
    int id;
    string name;
    Date date;
    string purpose;
};

// Global array & counter
Appointment schedule[50];
int countAppointments = 0;

void addAppointment();
void viewAppointmentsByDate();

int main() {
    srand(time(0));

    int choice;
    do {
        cout << "*********** Appointment Scheduler ***********\n";
        cout << "1. Add Appointment\n";
        cout << "2. View Appointments by Date\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(); 

        switch (choice) {
        case 1:
            addAppointment();
            break;
        case 2:
            viewAppointmentsByDate();
            break;
        case 3:
            cout << "Thank you for using the scheduler!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "---------------------------------------------\n";

    } while (choice != 3);

    return 0;
}

// Add Appointment
void addAppointment() {
    if (countAppointments >= 50) {
        cout << "Schedule is full! Cannot add more appointments.\n";
        return;
    }

    Appointment newApp;
    newApp.id = 1000 + rand() % 9000;

    cout << "Name: ";
    getline(cin, newApp.name);

    cout << "Date (DD MM YYYY): ";
    cin >> newApp.date.day >> newApp.date.month >> newApp.date.year;
    cin.ignore();

    cout << "Purpose: ";
    getline(cin, newApp.purpose);

   
    schedule[countAppointments++] = newApp;

    cout << "Appointment added! ID: " << newApp.id << endl;
}

// View Appointments by Date
void viewAppointmentsByDate() {
    Date searchDate;
    cout << "Enter date (DD MM YYYY): ";
    cin >> searchDate.day >> searchDate.month >> searchDate.year;

    bool found = false;
    cout << "Appointments on "
        << (searchDate.day < 10 ? "0" : "") << searchDate.day << "/"
        << (searchDate.month < 10 ? "0" : "") << searchDate.month << "/"
        << searchDate.year << ":\n";

    for (int i = 0; i < countAppointments; i++) {
        if (schedule[i].date.day == searchDate.day &&
            schedule[i].date.month == searchDate.month &&
            schedule[i].date.year == searchDate.year) {
            cout << "ID: " << schedule[i].id
                << " | " << schedule[i].name
                << " | " << schedule[i].purpose << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No appointments for this date.\n";
    }
}
