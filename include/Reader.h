//
// Created by Zhuolei on 1/5/2026.
//

#ifndef LIBRARYMANAGEMENT_READER_H
#define LIBRARYMANAGEMENT_READER_H

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Book.h"

using namespace std;

class Reader : public User {
public:
    Reader(string acc, string pwd) : User(acc, pwd, 2) {}

    void display();  // Display account information
    string getAccount();

    string getPassword();

    void changePassword(const string &newPwd);

    void borrowBook(const string &bookId);

    void returnBook(const string &bookId);

    void viewBorrowingHistory();

private:
    vector<string> borrowingHistory;  // Store borrowed book ID
};


#endif //LIBRARYMANAGEMENT_READER_H
