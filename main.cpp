#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits> // for clearing input buffer

// Include all module headers
#include "include/User.h"
#include "include/Reader.h"
#include "include/Admin.h"
#include "include/BorrowReturn.h"
#include "include/Ranking.h"
#include "include/Find.h"


using namespace std;

// --- Global Configuration ---
// Ensure this file exists in your build directory or use a relative path
const string READERS_FILE = "data/readers.txt";

// --- Function Declarations ---
void readerLogin();

void readerRegister();

void readerMenu(Reader *reader);

void adminLogin();

// Helper: Load all users for login verification
vector<User *> loadUsersForLogin() {
    vector<User *> users;
    ifstream fin(READERS_FILE);
    if (!fin) return users; // Return empty if file doesn't exist

    string account, password;
    while (fin >> account >> password) {
        // Logic: Accounts starting with a digit are Readers, others are Admins
        bool isReader = true;
        if (!account.empty() && !isdigit(account[0])) {
            isReader = false;
        }

        if (isReader) {
            users.push_back(new Reader(account, password));
        } else {
            users.push_back(new Admin(account, password));
        }
    }
    fin.close();
    return users;
}

int main() {
    int choice = 0;
    while (true) {
        cout << "\n=== Library Management System ===" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Reader Login / Register" << endl;
        cout << "3. Guest Book Search" << endl;
        cout << "4. View Rankings" << endl;
        cout << "0. Exit" << endl;
        cout << "Please enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2: {
                int subChoice;
                cout << "\n--- Reader Access ---\n";
                cout << "1. Login\n";
                cout << "2. Register\n";
                cout << "Choice: ";
                cin >> subChoice;
                if (subChoice == 1) readerLogin();
                else if (subChoice == 2) readerRegister();
                else cout << "Invalid option.\n";
                break;
            }
            case 3: {
                // Guest Search
                Find findSystem;
                findSystem.start();
                break;
            }
            case 4: {
                // Guest Ranking
                Ranking rankingSystem;
                rankingSystem.start();
                break;
            }
            case 0:
                cout << "Exiting system. Goodbye.\n";
                return 0;
            default:
                cout << "Invalid selection. Please try again.\n";
        }
    }
    return 0;
}

// --- Admin Logic ---
void adminLogin() {
    string account, password;
    cout << "Admin Account: ";
    cin >> account;
    cout << "Password: ";
    cin >> password;

    vector<User *> users = loadUsersForLogin();
    bool found = false;

    for (User *u: users) {
        // Validation: Account + Password + Role(1=Admin)
        if (u->account == account && u->checkPassword(password) && u->getRole() == 1) {
            cout << "Login successful.\n";
            Admin *admin = dynamic_cast<Admin *>(u);
            if (admin) {
                admin->start(); // Call Admin's internal menu
            }
            found = true;
            break;
        }
    }

    if (!found) cout << "Invalid admin credentials.\n";
    for (User *u: users) delete u; // Clean up memory
}

// --- Reader Logic ---
void readerLogin() {
    string account, password;
    cout << "Reader Account: ";
    cin >> account;
    cout << "Password: ";
    cin >> password;

    vector<User *> users = loadUsersForLogin();
    bool found = false;

    for (User *u: users) {
        // Validation: Account + Password + Role(2=Reader)
        if (u->account == account && u->checkPassword(password) && u->getRole() == 2) {
            cout << "Login successful.\n";
            Reader *reader = dynamic_cast<Reader *>(u);
            if (reader) {
                readerMenu(reader);
            }
            found = true;
            break;
        }
    }

    if (!found) cout << "Login failed. Invalid account or password.\n";
    for (User *u: users) delete u;
}

// --- Reader Register ---
void readerRegister() {
    string account, password;
    cout << "New Account (Numbers only): ";
    cin >> account;

    // Check for duplicates
    vector<User *> users = loadUsersForLogin();
    for (User *u: users) {
        if (u->account == account) {
            cout << "Account already exists! Please try a different one.\n";
            for (auto del: users) delete del;
            return;
        }
    }
    for (auto del: users) delete del;

    cout << "New Password: ";
    cin >> password;

    ofstream fout(READERS_FILE, ios::app);
    if (fout) {
        fout << account << " " << password << endl;
        cout << "Registration successful! You may now log in.\n";
    } else {
        cerr << "Error: Unable to save to file.\n";
    }
    fout.close();
}

// --- Reader Menu ---
void readerMenu(Reader *reader) {
    int choice;
    while (true) {
        cout << "\n===== Reader Menu (" << reader->account << ") =====\n";
        cout << "1. Borrow / Return System\n";
        cout << "2. Search Books\n";
        cout << "3. View Rankings\n";
        cout << "4. My Borrowing History\n";
        cout << "5. Change Password\n";
        cout << "0. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Call BorrowReturn module
                BorrowReturn br;
                br.start();
                break;
            }
            case 2: {
                Find f;
                f.start();
                break;
            }
            case 3: {
                Ranking r;
                r.start();
                break;
            }
            case 4:
                reader->viewBorrowingHistory();
                break;
            case 5: {
                string newPwd;
                cout << "Enter new password: ";
                cin >> newPwd;
                // Note: This only changes memory, not the file.
                // A full implementation would update readers.txt.
                reader->changePassword(newPwd);
                break;
            }
            case 0:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}