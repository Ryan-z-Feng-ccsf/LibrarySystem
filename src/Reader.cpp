//
// Created by Zhuolei on 1/5/2026.
//

#include "../include/Reader.h"
#include <fstream>
#include <sstream>

void Reader::display() {
    cout << "Account: " << account << endl;
    cout << "Password: " << password << endl;
}

string Reader::getAccount() {
    return account;
}

string Reader::getPassword() {
    return password;
}

void Reader::changePassword(const string &newPwd) {
    password = newPwd;
    cout << "Password changed successfully.\n";
}

void Reader::borrowBook(const string &bookId) {
    borrowingHistory.push_back(bookId);
}

void Reader::returnBook(const string &bookId) {
    for (size_t i = 0; i < borrowingHistory.size(); i++) {
        if (borrowingHistory[i] == bookId) {
            borrowingHistory.erase(borrowingHistory.begin() + i);
            break;
        }
    }
}

void Reader::viewBorrowingHistory() {
    ifstream file("data/borrowing_history.txt");
    if (!file.is_open()) {
        cout << "Unable to open borrowing history file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string acc, bookId;
        iss >> acc >> bookId;
        if (acc == account) {
            cout << "Book ID: " << bookId << " - ";
            int idNum = stoi(bookId);

            ifstream bookFile("data/books.txt");
            string bookLine;
            while (getline(bookFile, bookLine)) {
                istringstream bis(bookLine);
                int bId;
                string content;
                bis >> bId;
                getline(bis, content, '\0');
                if (bId == idNum) {
                    cout << content << endl;
                    break;
                }
            }
            bookFile.close();
        }
    }
    file.close();
}