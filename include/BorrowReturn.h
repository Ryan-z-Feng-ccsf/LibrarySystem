//
// Created by Zhuolei on 1/5/2026.
//

#ifndef LIBRARYMANAGEMENT_BORROWRETURN_H
#define LIBRARYMANAGEMENT_BORROWRETURN_H

#include "Reader.h"
#include "Book.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class BorrowReturn {
public:
    vector<Reader> readers;
    vector<Book> books; // Optional: If you wish to display book information during borrowing and returning.
    string borrowingHistoryFile = "data/borrowing_history.txt";

    void loadInformation(); // Read reader information and book information
    void saveBorrowingHistory(const string &account, const string &bookId);

    vector<pair<string, string>> loadBorrowingHistory();

    void menu();

    void start();

private:
    Reader *findReader(const string &account);

    void borrowBook();

    void returnBook();

    void viewBorrowingHistory();
};


#endif //LIBRARYMANAGEMENT_BORROWRETURN_H
