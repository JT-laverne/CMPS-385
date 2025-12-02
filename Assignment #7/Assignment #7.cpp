#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

struct Order {
    string id;
    string name;
    string item;
    int quantity;
    float price;
    string status;
};

// Function declarations
void loadOrders(vector<Order>& orders);
void saveOrders(const vector<Order>& orders);
void placeOrder(vector<Order>& orders);
void displayOrders(const vector<Order>& orders);
void markServed(vector<Order>& orders);
void salesSummary(const vector<Order>& orders);

int main() {
    vector<Order> orders;
    loadOrders(orders);

    int choice;
    do {
        cout << "\n****** Welcome to Restaurant Order Manager ******\n";
        cout << "1. Place New Order\n2. Display All Orders\n3. Mark Order as Served\n4. View Sales Summary\n5. Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: placeOrder(orders); break;
        case 2: displayOrders(orders); break;
        case 3: markServed(orders); break;
        case 4: salesSummary(orders); break;
        case 5:
            saveOrders(orders);
            cout << "Orders saved to orders.txt. Have a great day!\n";
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

// Load orders from file
void loadOrders(vector<Order>& orders) {
    ifstream fin("orders.txt");
    if (!fin) return;

    Order o;
    char comma;
    while (fin >> o.id >> comma >> o.name >> comma >> o.item >>
        comma >> o.quantity >> comma >> o.price >> comma >> o.status) {
        orders.push_back(o);
    }
    fin.close();
}

// Save orders to file
void saveOrders(const vector<Order>& orders) {
    ofstream fout("orders.txt");

    for (const auto& o : orders) {
        float total = o.quantity * o.price;
        fout << o.id << "," << o.name << "," << o.item << ","
            << o.quantity << "," << o.price << "," << total << ","
            << o.status << "\n";
    }
    fout.close();
}

// Place new order
void placeOrder(vector<Order>& orders) {
    Order o;
    cout << "Enter Order ID: ";
    cin >> o.id;
    cout << "Enter customer name: ";
    cin >> o.name;
    cout << "Enter menu item: ";
    cin >> o.item;
    cout << "Enter quantity: ";
    cin >> o.quantity;
    cout << "Enter price per item: ";
    cin >> o.price;
    o.status = "Pending";

    orders.push_back(o);
    cout << "Order added!\n";
}

// Display all orders
void displayOrders(const vector<Order>& orders) {
    cout << "\n=========== CURRENT ORDERS ===========\n";
    cout << left << setw(10) << "ID" << setw(12) << "Name"
        << setw(12) << "Item" << setw(6) << "Qty"
        << setw(8) << "Price" << setw(10) << "Total"
        << "Status\n";
    cout << "-------------------------------------------------------------\n";

    for (const auto& o : orders) {
        float total = o.quantity * o.price;
        cout << left << setw(10) << o.id
            << setw(12) << o.name
            << setw(12) << o.item
            << setw(6) << o.quantity
            << setw(8) << fixed << setprecision(2) << o.price
            << setw(10) << total
            << o.status << "\n";
    }
}

// Mark order as served
void markServed(vector<Order>& orders) {
    string id;
    cout << "Enter Order ID to mark as served: ";
    cin >> id;

    for (auto& o : orders) {
        if (o.id == id) {
            if (o.status == "Pending") {
                o.status = "Served";
                cout << "Order " << id << " marked as Served.\n";
            }
            else {
                cout << "Order already served.\n";
            }
            return;
        }
    }
    cout << "Order ID not found.\n";
}

// View sales summary
void salesSummary(const vector<Order>& orders) {
    int served = 0, pending = 0;
    float sales = 0;

    for (const auto& o : orders) {
        if (o.status == "Served") {
            served++;
            sales += o.quantity * o.price;
        }
        else {
            pending++;
        }
    }

    cout << "\n========== SALES SUMMARY ==========\n";
    cout << "Total Orders: " << orders.size() << "\n";
    cout << "Served: " << served << "\n";
    cout << "Pending: " << pending << "\n";
    cout << "Total Sales: $" << fixed << setprecision(2) << sales << "\n";
    cout << "===================================\n";
}
