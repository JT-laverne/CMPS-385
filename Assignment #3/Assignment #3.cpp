#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Base Class
class BankAccount {
protected:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    BankAccount() {
        accountHolderName = "";
        accountNumber = 0;
        balance = 0.0;
    }

    BankAccount(string name, int number, double initialBalance) {
        accountHolderName = name;
        accountNumber = number;
        balance = initialBalance;
    }

    virtual void deposit(double amount) {
        balance += amount;
    }

    virtual bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }

    virtual void displayBalance() const {
        cout << "Your current balance is $" << balance << "." << endl;
    }

    int getAccountNumber() const { return accountNumber; }
    string getName() const { return accountHolderName; }
    double getBalance() const { return balance; }
};

//Derived Class
class ChaseAccount : public BankAccount {
public:
    ChaseAccount() : BankAccount() {}

    ChaseAccount(string name, int number, double initialBalance)
        : BankAccount(name, number, initialBalance) {
    }

};

// Search Helper
int findAccount(ChaseAccount accounts[], int count, int acctNum) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].getAccountNumber() == acctNum)
            return i;
    }
    return -1;
}

//Main
int main() {
    ChaseAccount accounts[50];
    int accountCount = 0;

    srand(time(0));

    int choice;

    do {
        cout << "\n*************** Welcome to Chase ***************" << endl;
        cout << "Please choose one of the following operations" << endl;
        cout << "1 - Create a new bank account with an initial balance" << endl;
        cout << "2 - Deposit Money to an Account" << endl;
        cout << "3 - Withdraw Money from an Account" << endl;
        cout << "4 - Display Current Balance of an Account" << endl;
        cout << "0 - Exit" << endl;
        cout << "Type a number that you would like to perform: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string name;
            double initialBalance;

            cout << "Enter your name: ";
            getline(cin, name);

            cout << "Enter your initial balance: ";
            cin >> initialBalance;

            int randomAccountNumber = rand() % 900000 + 100000;

            accounts[accountCount] = ChaseAccount(name, randomAccountNumber, initialBalance);
            accountCount++;

            cout << "\nCongratulations " << name
                << "! You have successfully opened your new bank account "
                << "with an initial balance of $" << initialBalance
                << ". Your account number is " << randomAccountNumber << ".\n";

            system("pause");
        }

        else if (choice == 2) {
            int acctNum;
            cout << "Enter the account number: ";
            cin >> acctNum;

            int index = findAccount(accounts, accountCount, acctNum);

            if (index == -1) {
                cout << "No account number exists!\n";
                system("pause");
            }
            else {
                double depositAmount;
                cout << "Enter the amount that you would like to deposit: ";
                cin >> depositAmount;

                accounts[index].deposit(depositAmount);

                cout << "\nCongratulations " << accounts[index].getName()
                    << "! You have successfully deposited the amount of $"
                    << depositAmount << " in your account #"
                    << acctNum << ". Your current balance is $"
                    << accounts[index].getBalance() << ".\n";

                system("pause");
            }
        }

        else if (choice == 3) {
            int acctNum;
            cout << "Enter the account number: ";
            cin >> acctNum;

            int index = findAccount(accounts, accountCount, acctNum);

            if (index == -1) {
                cout << "No account number exists!\n";
                system("pause");
            }
            else {
                double withdrawAmount;
                cout << "Enter the amount that you would like to withdraw: ";
                cin >> withdrawAmount;

                if (accounts[index].withdraw(withdrawAmount)) {
                    cout << "\nCongratulations " << accounts[index].getName()
                        << "! You have successfully withdrawn the amount of $"
                        << withdrawAmount << " in your account #"
                        << acctNum << ". Your current balance is $"
                        << accounts[index].getBalance() << ".\n";
                }
                else {
                    cout << "Insufficient funds! Withdrawal failed.\n";
                }
                system("pause");
            }
        }

        else if (choice == 4) {
            int acctNum;
            cout << "Enter the account number: ";
            cin >> acctNum;

            int index = findAccount(accounts, accountCount, acctNum);

            if (index == -1) {
                cout << "No account number exists!\n";
                system("pause");
            }
            else {
                accounts[index].displayBalance();
                system("pause");
            }
        }

    } while (choice != 0);

    cout << "Goodbye!" << endl;
    return 0;
}
