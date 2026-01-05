//
// Created by Zhuolei on 1/5/2026.
//

#ifndef LIBRARYMANAGEMENT_ADMIN_H
#define LIBRARYMANAGEMENT_ADMIN_H


#include "User.h"
#include "Reader.h"
#include "Book.h"
#include "Ranking.h"
#include "Find.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> // For algorithms such as remove_if

using namespace std;

class Admin : public User {
public:
    Admin(string acc, string pwd) : User(acc, pwd, 1) {}

    void display() override {
        cout << "Admin Account: " << account << endl;
    }

    void start();

private:
    void adminMenu();

    void manageReaders();

    void manageBooks(); // This function now serves as the entry point for book management.
    void viewRanking();

    void findBooks();

    // --- Newly Added Utility Functions ---
    void addBook(vector<Book> &books);

    void deleteBook(vector<Book> &books);

    void updateBook(vector<Book> &books);

    // File Read/Write Assistant
    void loadBooks(vector<Book> &books);

    void saveBooks(const vector<Book> &books);
};


#endif //LIBRARYMANAGEMENT_ADMIN_H
