#include <iostream>
#include <string>
using namespace std;

class Item {
private:
    string name;
    double price;

protected:
    Item(string n, double p) : name(n), price(p) {}

public:
    string getName() const { return name; }
    virtual double getPrice() const = 0;
    virtual void display() const = 0;
    virtual void receiptEntry() const = 0;

    virtual ~Item() {}
};


class FoodItem : public Item {
private:
    string expirationDate;

public:
    FoodItem(string n, double p, string exp)
        : Item(n, p), expirationDate(exp) {
    }

    double getPrice() const override {
        return Item::getName(), 0, Item::getPrice(), 0;
    }

    void display() const override {
        cout << "Name: " << getName()
            << " | Price: $" << getPrice()
            << " | Exp: " << expirationDate << endl;
    }

    void receiptEntry() const override {
        cout << getName() << " - $" << getPrice() << endl;
    }

    double getPrice() const override {
        return Item::getPrice();
    }
};


class ElectronicItem : public Item {
private:
    int warrantyMonths;

public:
    ElectronicItem(string n, double p, int w)
        : Item(n, p), warrantyMonths(w) {
    }

    double getPrice() const override {
        return Item::getPrice();
    }

    void display() const override {
        cout << "Name: " << getName()
            << " | Price: $" << getPrice()
            << " | Warranty: " << warrantyMonths << " months" << endl;
    }

    void receiptEntry() const override {
        cout << getName() << " - $" << getPrice() << endl;
    }
};

int main() {
    Item* store[50];
    Item* purchases[20];

    int storeCount = 0;
    int purchaseCount = 0;

    int choice;

    cout << "****************** Welcome to QuickMart POS ******************" << endl;

    do {
        cout << "\n1 - Add item to store" << endl;
        cout << "2 - Display available items" << endl;
        cout << "3 - Buy item by name" << endl;
        cout << "4 - View receipt" << endl;
        cout << "0 - Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string type;
            cout << "Enter item type (Food/Electronic): ";
            getline(cin, type);

            string name;
            double price;

            cout << "Enter item name: ";
            getline(cin, name);

            cout << "Enter price: ";
            cin >> price;
            cin.ignore();

            if (type == "Food" || type == "food") {
                string exp;
                cout << "Enter expiration date: ";
                getline(cin, exp);

                store[storeCount++] = new FoodItem(name, price, exp);
            }
            else if (type == "Electronic" || type == "electronic") {
                int w;
                cout << "Enter warranty in months: ";
                cin >> w;

                store[storeCount++] = new ElectronicItem(name, price, w);
            }
            else {
                cout << "Invalid type!" << endl;
                continue;
            }

            cout << "Item added successfully!" << endl;
        }

        else if (choice == 2) {
            if (storeCount == 0) {
                cout << "No items in store." << endl;
            }
            else {
                for (int i = 0; i < storeCount; i++) {
                    store[i]->display();
                }
            }
        }

        else if (choice == 3) {
            string searchName;
            cout << "Enter item name: ";
            getline(cin, searchName);

            bool found = false;
            for (int i = 0; i < storeCount; i++) {
                if (store[i]->getName() == searchName) {
                    purchases[purchaseCount++] = store[i];
                    cout << "Purchased " << searchName << " for $"
                        << store[i]->getPrice() << endl;
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Item not found." << endl;
        }

        else if (choice == 4) {
            if (purchaseCount == 0) {
                cout << "No purchases yet." << endl;
            }
            else {
                cout << "---- Receipt ----" << endl;
                double total = 0;

                for (int i = 0; i < purchaseCount; i++) {
                    cout << (i + 1) << ". ";
                    purchases[i]->receiptEntry();
                    total += purchases[i]->getPrice();
                }

                cout << "Total: $" << total << endl;
            }
        }

    } while (choice != 0);

    cout << "Thank you for shopping at QuickMart!" << endl;

    //Memory Cleanup
    for (int i = 0; i < storeCount; i++) {
        delete store[i];
    }

    return 0;
}
