#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Item {
    string name;
    string category;
    int quantity;
    double price;
};

struct Transaction {
    string type;  // buy/return
    string itemName;
    int quantity;
    double unitPrice;
};

// Function Declarations
int loadInventory(Item items[]);
void saveInventory(Item items[], int count);
void saveTransaction(Transaction t);
void displayInventory(Item items[], int count);
void buyItem(Item items[], int count);
void returnItem(Item items[], int count);
void showProfitReport();


//Load Inventory from inventory.txt
int loadInventory(Item items[]) {
    ifstream file("inventory.txt");
    if (!file.is_open()) return 0;

    string line;
    int count = 0;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, category, qtyStr, priceStr;

        getline(ss, name, ',');
        getline(ss, category, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');

        items[count].name = name;
        items[count].category = category;
        items[count].quantity = stoi(qtyStr);
        items[count].price = stod(priceStr);

        count++;
    }
    file.close();
    return count;
}

//Save Inventory to inventory.txt
void saveInventory(Item items[], int count) {
    ofstream file("inventory.txt");
    file << "Name,Category,Quantity,Price\n";
    for (int i = 0; i < count; i++) {
        file << items[i].name << ","
            << items[i].category << ","
            << items[i].quantity << ","
            << fixed << setprecision(2) << items[i].price << "\n";
    }
    file.close();
}

//Save a transaction to transactions.txt
void saveTransaction(Transaction t) {
    ofstream file("transactions.txt", ios::app);
    file << t.type << ","
        << t.itemName << ","
        << t.quantity << ","
        << fixed << setprecision(2) << t.unitPrice << "\n";
    file.close();
}

// Display Current Inventory
void displayInventory(Item items[], int count) {
    cout << "============== INVENTORY ==============\n";
    cout << left << setw(15) << "Item Name"
        << setw(15) << "Category"
        << setw(8) << "Qty"
        << setw(10) << "Price" << "\n";
    cout << "---------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << items[i].name
            << setw(15) << items[i].category
            << setw(8) << items[i].quantity
            << "$" << fixed << setprecision(2) << items[i].price << "\n";
    }
}

// Buy Item
void buyItem(Item items[], int count) {
    string name;
    int qty;

    cout << "Enter item to buy: ";
    cin >> name;
    cout << "Quantity: ";
    cin >> qty;

    for (int i = 0; i < count; i++) {
        if (items[i].name == name) {
            if (items[i].quantity < qty) {
                cout << "Not enough stock.\n";
                return;
            }

            items[i].quantity -= qty;

            double totalCost = qty * items[i].price;

            Transaction t{ "BUY", name, qty, items[i].price };
            saveTransaction(t);

            cout << "Successfully purchased " << qty << " x " << name
                << " for $" << fixed << setprecision(2) << totalCost << "\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

// Return Item
void returnItem(Item items[], int count) {
    string name;
    int qty;

    cout << "Enter item to return: ";
    cin >> name;
    cout << "Quantity: ";
    cin >> qty;

    for (int i = 0; i < count; i++) {
        if (items[i].name == name) {
            items[i].quantity += qty;

            Transaction t{ "RETURN", name, qty, items[i].price };
            saveTransaction(t);

            cout << qty << " x " << name << " returned and added back to inventory.\n";
            return;
        }
    }
    cout << "Item not found.\n";
}

// Profit Report
void showProfitReport() {
    ifstream file("transactions.txt");
    if (!file.is_open()) {
        cout << "No transactions found.\n";
        return;
    }

    string line;
    getline(file, line);

    double revenue = 0;
    double refunds = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string type, name, qtyStr, priceStr;

        getline(ss, type, ',');
        getline(ss, name, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');

        int qty = stoi(qtyStr);
        double price = stod(priceStr);

        if (type == "BUY")
            revenue += qty * price;
        else if (type == "RETURN")
            refunds += qty * price;
    }

    file.close();

    cout << "========== PROFIT REPORT ==========\n";
    cout << "Total Revenue: $" << fixed << setprecision(2) << revenue << "\n";
    cout << "Total Refunds: $" << fixed << setprecision(2) << refunds << "\n";
    cout << "Net Profit:    $" << fixed << setprecision(2) << (revenue - refunds) << "\n";
    cout << "==================================\n";
}

//Main Menu
int main() {
    Item items[100];
    int itemCount = loadInventory(items);

    int choice;

    cout << "******** Welcome to Store Inventory & Profit Tracker ********\n";

    do {
        cout << "\nPlease choose one of the following operations:\n";
        cout << "1. Add New Item to Inventory\n";
        cout << "2. Display Inventory\n";
        cout << "3. Buy Item\n";
        cout << "4. Return Item\n";
        cout << "5. View Profit Report\n";
        cout << "6. Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter item name: ";
            cin >> items[itemCount].name;
            cout << "Enter category: ";
            cin >> items[itemCount].category;
            cout << "Enter quantity: ";
            cin >> items[itemCount].quantity;
            cout << "Enter price: ";
            cin >> items[itemCount].price;

            itemCount++;

            cout << "Item added!\n";
            break;
        }

        case 2:
            displayInventory(items, itemCount);
            break;

        case 3:
            buyItem(items, itemCount);
            break;

        case 4:
            returnItem(items, itemCount);
            break;

        case 5:
            showProfitReport();
            break;

        case 6:
            saveInventory(items, itemCount);
            cout << "Inventory and transactions saved. Goodbye!\n";
            break;

        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
