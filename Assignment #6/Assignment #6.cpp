#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

template <typename T1, typename T2>
struct Package {
    T1 id;
    string name;
    string type;
    int etaHours;
    T2 fee;
    string status;
};

// Load Packages
template <typename T1, typename T2>
int loadPackages(Package<T1, T2> packages[]) {
    ifstream file("packages.txt");
    if (!file.is_open()) return 0;

    string line;
    getline(file, line);

    int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, type, etaStr, feeStr, status;

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, etaStr, ',');
        getline(ss, feeStr, ',');
        getline(ss, status, ',');

        packages[count].id = static_cast<T1>(stoi(idStr));
        packages[count].name = name;
        packages[count].type = type;
        packages[count].etaHours = stoi(etaStr);
        packages[count].fee = static_cast<T2>(stod(feeStr));
        packages[count].status = status;

        count++;
    }
    return count;
}

// Save packages
template <typename T1, typename T2>
void savePackages(Package<T1, T2> packages[], int count) {
    ofstream file("packages.txt");
    file << "ID,Name,Type,ETA,Fee,Status\n";
    for (int i = 0; i < count; i++) {
        file << packages[i].id << ","
            << packages[i].name << ","
            << packages[i].type << ","
            << packages[i].etaHours << ","
            << fixed << setprecision(2) << packages[i].fee << ","
            << packages[i].status << "\n";
    }
}

// Add Package
template <typename T1, typename T2>
void addPackage(Package<T1, T2> packages[], int& count) {
    cout << "Enter package ID: ";
    cin >> packages[count].id;

    cout << "Enter recipient name: ";
    cin >> packages[count].name;

    cout << "Enter delivery type (Standard/Express/Fragile): ";
    cin >> packages[count].type;

    cout << "Enter delivery ETA (in hours): ";
    cin >> packages[count].etaHours;

    cout << "Enter delivery fee: ";
    cin >> packages[count].fee;

    packages[count].status = "Pending";

    count++;

    cout << "Package added!\n";
}

// Display Packages
template <typename T1, typename T2>
void displayPackages(Package<T1, T2> packages[], int count) {
    cout << "============ PACKAGES ============\n";
    cout << left << setw(10) << "ID"
        << setw(12) << "Name"
        << setw(12) << "Type"
        << setw(6) << "ETA"
        << setw(10) << "Fee"
        << "Status\n";

    cout << "-----------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << packages[i].id
            << setw(12) << packages[i].name
            << setw(12) << packages[i].type
            << setw(6) << packages[i].etaHours
            << "$" << fixed << setprecision(2) << setw(9) << packages[i].fee
            << packages[i].status << "\n";
    }
}

// Package Delivered
template <typename T1, typename T2>
void markDelivered(Package<T1, T2> packages[], int count) {
    T1 id;
    cout << "Enter package ID to mark as delivered: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (packages[i].id == id) {
            packages[i].status = "Delivered";
            cout << "Package " << id << " marked as Delivered.\n";
            return;
        }
    }
    cout << "Package not found.\n";
}

// Delivery report
template <typename T1, typename T2>
void deliveryReport(Package<T1, T2> packages[], int count) {
    int delivered = 0;
    double revenue = 0;

    for (int i = 0; i < count; i++) {
        if (packages[i].status == "Delivered") {
            delivered++;
            revenue += packages[i].fee;
        }
    }

    cout << "========== DELIVERY REPORT ==========\n";
    cout << "Total Packages: " << count << "\n";
    cout << "Delivered: " << delivered << "\n";
    cout << "Pending: " << count - delivered << "\n";
    cout << "Total Revenue: $" << fixed << setprecision(2) << revenue << "\n";
    cout << "=====================================\n";
}

// Main
int main() {
    Package<int, double> packages[100];

    int count = loadPackages(packages);

    int choice;

    do {
        cout << "\n******** Welcome to Package Delivery Tracker ********\n";
        cout << "1. Add New Package\n"
            << "2. Display All Packages\n"
            << "3. Mark Package as Delivered\n"
            << "4. View Delivery Report\n"
            << "5. Exit\n→ ";

        cin >> choice;

        switch (choice) {
        case 1: addPackage(packages, count); break;
        case 2: displayPackages(packages, count); break;
        case 3: markDelivered(packages, count); break;
        case 4: deliveryReport(packages, count); break;
        case 5:
            savePackages(packages, count);
            cout << "Data saved to packages.txt. Goodbye!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
