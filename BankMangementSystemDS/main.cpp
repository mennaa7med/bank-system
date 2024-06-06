#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct Account {
    string accountNumber;
    string name;
    string password;
    double balance;
    Account* next;
};

class BankManagementSystem {
private:
    Account* head;
    string dataFile;

public:
    BankManagementSystem() : head(NULL), dataFile("account.txt") {}

    void addAccount() {
        Account* newAccount = new Account;
        cout << "Enter Account Number: ";
        cin >> newAccount->accountNumber;

        if (isAccountNumberUnique(newAccount->accountNumber)) {
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, newAccount->name);
            cout << "Set password: ";
            cin >> newAccount->password;
            cout << "Enter Initial Balance: ";
            cin >> newAccount->balance;
            newAccount->next = NULL;

            if (head == NULL) {
                head = newAccount;
            } else {
                Account* current = head;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newAccount;
            }
            cout << "Account Added Successfully!" << endl;
            saveAccountsToFile();
        } else {
            cout << "Account Number is not unique. Please enter a unique account number." << endl;
            delete newAccount;
        }
    }

    bool isAccountNumberUnique(const string& accountNumber) {
        Account* current = head;
        while (current != NULL) {
            if (current->accountNumber == accountNumber) {
                return false;
            }
            current = current->next;
        }
        return true;
    }

    Account* findAccount(const string& accountNumber, const string& password) {
        Account* current = head;
        while (current != NULL) {
            if (current->accountNumber == accountNumber && current->password == password) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void searchAccount() {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        string password;
        cout << "Enter Password: ";
        cin >> password;
        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            cout << "Account Number: " << account->accountNumber << endl;
            cout << "Name: " << account->name << endl;
            cout << "Balance: " << account->balance << endl;
        } else {
            cout << "Account not found or invalid password!" << endl;
        }
    }

    void depositFunds() {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        string password;
        cout << "Enter Password: ";
        cin >> password;
        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            double amount;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            account->balance += amount;
            cout << "Deposit Successful!" << endl;
            saveAccountsToFile();
        } else {
            cout << "Account not found or invalid password!" << endl;
        }
    }

    void withdrawFunds() {
        string accountNumber;
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        string password;
        cout << "Enter Password: ";
        cin >> password;
        Account* account = findAccount(accountNumber, password);
        if (account != NULL) {
            double amount;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            if (account->balance >= amount) {
                account->balance -= amount;
                cout << "Withdrawal Successful!" << endl;
                saveAccountsToFile();
            } else {
                cout << "Insufficient funds." << endl;
            }
        } else {
            cout << "Account not found or invalid password!" << endl;
        }
    }

    void displayAccount() {
        cout << "------All Accounts------" << endl;
        Account* current = head;
        while (current != NULL) {
            cout << "Account Number: " << current->accountNumber << endl;
            cout << "Name: " << current->name << endl;
            cout << "Balance: " << current->balance << endl;
            current = current->next;
        }
        cout << endl;
    }

    int count() {
        int count = 0;
        Account* current = head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    }

    void saveAccountsToFile() {
        ofstream outputFile(dataFile.c_str());
        if (outputFile.is_open()) {
            Account* current = head;
            while (current != NULL) {
                outputFile << current->accountNumber << "," << current->name << "," << current->password << "," << current->balance << endl;
                current = current->next;
            }
            outputFile.close();
            cout << "Accounts saved to file: " << dataFile << endl;
        } else {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    void loadAccountsFromFile() {
        ifstream inputFile(dataFile.c_str());
        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                stringstream ss(line);
                string accountNumber, name, password;
                double balance;
                getline(ss, accountNumber, ',');
                getline(ss, name, ',');
                getline(ss, password, ',');
                ss >> balance;
                Account* newAccount = new Account;
                newAccount->accountNumber = accountNumber;
                newAccount->name = name;
                newAccount->password = password;
                newAccount->balance = balance;
                newAccount->next = NULL;
                if (head == NULL) {
                    head = newAccount;
                } else {
                    Account* current = head;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newAccount;
                }
            }
            inputFile.close();
            cout << "Accounts loaded from file: " << dataFile << endl;
        } else {
            cout << "Error: Unable to open file for reading." << endl;
        }
    }

    void menu() {
        loadAccountsFromFile();
        int choice;
        while (true) {
            cout << "\n...Bank Management System..." << endl;
            cout << "1. Add Account" << endl;
            cout << "2. Search Account" << endl;
            cout << "3. Deposit Funds" << endl;
            cout << "4. Withdraw Funds" << endl;
            cout << "5. Display All Accounts" << endl;
            cout << "6. Count Accounts" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    addAccount();
                    break;
                case 2:
                    searchAccount();
                    break;
                case 3:
                    depositFunds();
                    break;
                case 4:
                    withdrawFunds();
                    break;
                case 5:
                    displayAccount();
                    break;
                case 6:
                    cout << "Total number of accounts: " << count() << endl;
                    break;
                case 7:
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
};

int main() {
    BankManagementSystem bankManagementSystem;
    bankManagementSystem.menu();
    return 0;
}
