#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
using namespace std;

//Registered User Struct
struct RegisteredUser {
    string name;
    long long id; // MUST be ≥ 7 digits
    int row, col;
    bool inLot;
    time_t timeEntered;
    time_t timeLeft;
};

//Visitor Struct
struct Visitor {
    string name;
    int tempID; // ≤ 3 digits
    int row, col;
    time_t timeEntered;
    time_t timeLeft;
};

//Reservation
vector<vector<int>> parkingLot; // 0 vacant, 1 occupied
vector<RegisteredUser> registeredUsers;
vector<Visitor> visitors;

const double RATE_PER_HOUR = 2.50; // parking fee

//Reservation (Doubly Linked List)
struct ReservationNode {
    long long userID;
    int preferredRow;
    int preferredCol;
    ReservationNode* prev;
    ReservationNode* next;
};

// Add reservation to doubly linked list
void addReservation(long long userID, int prefRow, int prefCol) {
    ReservationNode* node = new ReservationNode{
        userID, prefRow, prefCol, nullptr, nullptr
    };

    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

// Find reservation by user ID
ReservationNode* findReservation(long long userID) {
    ReservationNode* curr = head;
    while (curr) {
        if (curr->userID == userID)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}


ReservationNode* head = nullptr;
ReservationNode* tail = nullptr;

//Display Parking Lot
void displayParkingLot() {
    cout << "\nParking Lot (0 = Vacant, 1 = Occupied)\n   ";
    for (int c = 0; c < parkingLot[0].size(); c++)
        cout << " C" << c << " ";
    cout << endl;

    for (int r = 0; r < parkingLot.size(); r++) {
        cout << "R" << r << " ";
        for (int c = 0; c < parkingLot[0].size(); c++)
            cout << setw(3) << parkingLot[r][c] << " ";
        cout << endl;
    }
}

//Calculate Parking Fee
double calculateFee(time_t in, time_t out) {
    double hours = difftime(out, in) / 3600.0;
    if (hours < 1) hours = 1; // minimum charge
    return hours * RATE_PER_HOUR;
}

//Assign Parking Spot
bool assignSpot(int& row, int& col) {
    for (int r = 0; r < parkingLot.size(); r++)
        for (int c = 0; c < parkingLot[0].size(); c++)
            if (parkingLot[r][c] == 0) {
                parkingLot[r][c] = 1;
                row = r; col = c;
                return true;
            }
    return false;
}

//Register User
void registerUser() {
    RegisteredUser u;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, u.name);

    do {
        cout << "Enter ID (≥ 7 digits): ";
        cin >> u.id;
    } while (u.id < 1000000);

    int prefRow, prefCol;
    cout << "Enter preferred parking row: ";
    cin >> prefRow;
    cout << "Enter preferred parking column: ";
    cin >> prefCol;

	// Save preference Doubly Linked List
    addReservation(u.id, prefRow, prefCol);

    // Try to assign preferred spot first
    if (prefRow >= 0 && prefRow < parkingLot.size() &&
        prefCol >= 0 && prefCol < parkingLot[0].size() &&
        parkingLot[prefRow][prefCol] == 0) {

        parkingLot[prefRow][prefCol] = 1;
        u.row = prefRow;
        u.col = prefCol;
    }
    else if (!assignSpot(u.row, u.col)) {
        cout << "Parking lot full.\n";
        u.inLot = false;
        registeredUsers.push_back(u);
        return;
    }

    u.inLot = true;
    u.timeEntered = time(0);
    cout << "Parked at [" << u.row << "," << u.col << "]\n";

    registeredUsers.push_back(u);
}


//Visitor Entry
void visitorEntry() {
    Visitor v;
    cout << "Enter visitor name: ";
    cin.ignore(); getline(cin, v.name);

    do {
        cout << "Enter temporary ID (≤ 3 digits): ";
        cin >> v.tempID;
    } while (v.tempID > 999);

    if (!assignSpot(v.row, v.col)) {
        cout << "Parking lot full.\n";
        return;
    }

    v.timeEntered = time(0);
    visitors.push_back(v);
    cout << "Visitor parked at [" << v.row << "," << v.col << "]\n";
}

//Exit by ID
void exitByID() {
    long long id;
    cout << "Enter ID (registered or visitor): ";
    cin >> id;

    for (auto& u : registeredUsers) {
        if (u.id == id && u.inLot) {
            u.timeLeft = time(0);
            parkingLot[u.row][u.col] = 0;
            u.inLot = false;
            cout << "Exit successful. Fee: $" << calculateFee(u.timeEntered, u.timeLeft) << endl;
            return;
        }
    }

    for (auto& v : visitors) {
        if (v.tempID == id) {
            v.timeLeft = time(0);
            parkingLot[v.row][v.col] = 0;
            cout << "Exit successful. Fee: $" << calculateFee(v.timeEntered, v.timeLeft) << endl;
            return;
        }
    }

    cout << "ID not found.\n";
}

//Search by ID
void searchByID() {
    long long id;
    cout << "Enter ID to search: ";
    cin >> id;

    for (auto& u : registeredUsers) {
        if (u.id == id) {
            cout << "Registered User: " << u.name << endl;
            cout << "In Lot: " << (u.inLot ? "Yes" : "No") << endl;

            if (u.inLot)
                cout << "Current Spot: [" << u.row << "," << u.col << "]\n";

            ReservationNode* res = findReservation(id);
            if (res) {
                cout << "Preferred Spot: ["
                    << res->preferredRow << ","
                    << res->preferredCol << "]\n";
            }
            return;
        }
    }

    for (auto& v : visitors) {
        if (v.tempID == id) {
            cout << "Visitor: " << v.name << endl;
            cout << "Current Spot: [" << v.row << "," << v.col << "]\n";
            return;
        }
    }

    cout << "ID not found.\n";
}


//Main Function
int main() {
    int rows, cols;
    cout << "Enter parking lot size (rows cols): ";
    cin >> rows >> cols;
    parkingLot.assign(rows, vector<int>(cols, 0));

    int choice;
    do {
        cout << "\n==== Parking System ====";
        cout << "\n1. Register User";
        cout << "\n2. Visitor Entry";
        cout << "\n3. Exit Parking";
        cout << "\n4. Search by ID";
        cout << "\n5. Display Parking Lot";
        cout << "\n0. Exit";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1: registerUser(); break;
        case 2: visitorEntry(); break;
        case 3: exitByID(); break;
        case 4: searchByID(); break;
        case 5: displayParkingLot(); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}
