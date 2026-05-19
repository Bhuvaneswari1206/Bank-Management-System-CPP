#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

class BankAccount {

private:
    int accountNumber;
    string name;
    float balance;

public:

    // Create new account
    void createAccount() {

        ofstream file("bankmanagementsystem.txt", ios::app);

        // Check file opening
        if (!file) {
            cout << "\nError in opening file.";
            return;
        }

        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Initial Balance: ";
        cin >> balance;

        // Store data in file
        file << accountNumber << endl;
        file << name << endl;
        file << balance << endl;

        file.close();

        cout << "\nAccount Created Successfully!" << endl;
    }

    // Check account balance
    void checkBalance() {

        ifstream file("bankmanagementsystem.txt");

        if (!file) {
            cout << "\nError in opening file.";
            return;
        }

        int searchAccountNumber;
        bool found = false;

        cout << "\nEnter Account Number: ";
        cin >> searchAccountNumber;

        // Read file data
        while (file >> accountNumber) {

            file.ignore();

            getline(file, name);

            file >> balance;

            file.ignore();

            if (accountNumber == searchAccountNumber) {

                cout << "\nAccount Number : " << accountNumber << endl;
                cout << "Customer Name  : " << name << endl;
                cout << "Balance        : " << balance << endl;

                found = true;
                break;
            }
        }

        if (!found) {
            cout << "\nAccount not found.";
        }

        file.close();
    }

    // Deposit money
    void deposit() {

        ifstream file("bankmanagementsystem.txt");
        ofstream temp("temp.txt");

        if (!file || !temp) {
            cout << "\nFile opening error.";
            return;
        }

        int searchAccountNumber;
        float amount;
        bool found = false;

        cout << "\nEnter Account Number: ";
        cin >> searchAccountNumber;

        while (file >> accountNumber) {

            file.ignore();

            getline(file, name);

            file >> balance;

            file.ignore();

            if (accountNumber == searchAccountNumber) {

                cout << "Enter Amount to Deposit: ";
                cin >> amount;

                balance = balance + amount;

                cout << "\nAmount Deposited Successfully!";
                found = true;
            }

            // Write updated data
            temp << accountNumber << endl;
            temp << name << endl;
            temp << balance << endl;
        }

        if (!found) {
            cout << "\nAccount not found.";
        }

        file.close();
        temp.close();

        // Replace old file
        remove("bankmanagementsystem.txt");
        rename("temp.txt", "bankmanagementsystem.txt");
    }

    // Withdraw money
    void withdraw() {

        ifstream file("bankmanagementsystem.txt");
        ofstream temp("temp.txt");

        if (!file || !temp) {
            cout << "\nFile opening error.";
            return;
        }

        int searchAccountNumber;
        float amount;
        bool found = false;

        cout << "\nEnter Account Number: ";
        cin >> searchAccountNumber;

        while (file >> accountNumber) {

            file.ignore();

            getline(file, name);

            file >> balance;

            file.ignore();

            if (accountNumber == searchAccountNumber) {

                cout << "Enter Amount to Withdraw: ";
                cin >> amount;

                // Check balance
                if (amount <= balance) {

                    balance = balance - amount;

                    cout << "\nAmount Withdrawn Successfully!";
                }
                else {
                    cout << "\nInsufficient Balance.";
                }

                found = true;
            }

            temp << accountNumber << endl;
            temp << name << endl;
            temp << balance << endl;
        }

        if (!found) {
            cout << "\nAccount not found.";
        }

        file.close();
        temp.close();

        remove("bankmanagementsystem.txt");
        rename("temp.txt", "bankmanagementsystem.txt");
    }
};

int main() {

    BankAccount b;

    int choice;
    char continueChoice;

    do {

        cout << "\n========== BANK MANAGEMENT SYSTEM ==========";
        cout << "\n1. Create Account";
        cout << "\n2. Check Balance";
        cout << "\n3. Deposit Money";
        cout << "\n4. Withdraw Money";
        cout << "\n5. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            b.createAccount();
            break;

        case 2:
            b.checkBalance();
            break;

        case 3:
            b.deposit();
            break;

        case 4:
            b.withdraw();
            break;

        case 5:
            return 0;

        default:
            cout << "\nInvalid Choice.";
        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> continueChoice;

    } while (continueChoice == 'y' || continueChoice == 'Y');

    return 0;
}