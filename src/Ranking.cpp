//
// Created by Zhuolei on 1/5/2026.
//

#include "../include/Ranking.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool compareBBook(const BBook &a, const BBook &b) {
    return a.borrowCount > b.borrowCount;
}

bool compareRReader(const RReader &a, const RReader &b) {
    return a.borrowCount > b.borrowCount;
}

bool compareDate(const Book &a, const Book &b) {
    return a.getDate() > b.getDate(); // Assume Book has getDate()
}

void Ranking::loadBorrowRecords(vector<BBook> &bbooks, vector<RReader> &rreaders) {
    ifstream fin("data/borrowing_history.txt");
    if (!fin) return;

    string account, bookId;
    while (fin >> account >> bookId) {
        auto itBook = find_if(bbooks.begin(), bbooks.end(), [&](const BBook &b) { return b.id == bookId; });
        if (itBook != bbooks.end()) itBook->borrowCount++;
        else bbooks.push_back({bookId, 1});

        auto itReader = find_if(rreaders.begin(), rreaders.end(),
                                [&](const RReader &r) { return r.account == account; });
        if (itReader != rreaders.end()) itReader->borrowCount++;
        else rreaders.push_back({account, 1});
    }
    fin.close();
}

void Ranking::showTopReaders(const vector<RReader> &rreaders) {
    vector<RReader> sorted = rreaders;
    sort(sorted.begin(), sorted.end(), compareRReader);
    cout << "===== Top 10 Borrowing Readers =====" << endl;
    for (int i = 0; i < min(10, (int) sorted.size()); i++) {
        cout << i + 1 << ". " << sorted[i].account
             << ", Borrowed Books: " << sorted[i].borrowCount << endl;
    }
}

void Ranking::showTopBooks(const vector<BBook> &bbooks) {
    vector<BBook> sorted = bbooks;
    sort(sorted.begin(), sorted.end(), compareBBook);
    cout << "===== Top 10 Borrowed Books =====" << endl;

    for (int i = 0; i < min(10, (int) sorted.size()); i++) {
        cout << i + 1 << ". " << sorted[i].id << " ";

        ifstream fin("data/books.txt");
        string line;
        while (getline(fin, line)) {
            istringstream iss(line);
            int idNum;
            string content;
            iss >> idNum;
            getline(iss, content);
            if (to_string(idNum) == sorted[i].id) {
                cout << content << endl;
                break;
            }
        }
        fin.close();
        cout << "Borrow Count: " << sorted[i].borrowCount << endl;
    }
}

void Ranking::showNewestBooks() {
    vector<Book> books;
    ifstream file("data/books.txt");
    if (!file) {
        cout << "Unable to open books.txt" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id;
        string ISBN, name, author, publisher, date;
        float price;
        int quantity;

        iss >> id;
        iss.ignore();
        getline(iss, ISBN, '\t');
        getline(iss, name, '\t');
        getline(iss, author, '\t');
        getline(iss, publisher, '\t');
        getline(iss, date, '\t');
        iss >> price;
        iss.ignore();
        iss >> quantity;

        books.push_back(Book(id, 0, ISBN, name, author, publisher, date, price, quantity));
    }
    file.close();

    sort(books.begin(), books.end(), compareDate);

    cout << "===== Top 10 Newest Books =====" << endl;
    for (int i = 0; i < min(10, (int) books.size()); i++) {
        books[i].print(); // assume Book has print()
        cout << endl;
    }
}

void Ranking::menu() {
    cout << "====== Ranking Menu ======" << endl;
    cout << "1. Top 10 Borrowing Readers" << endl;
    cout << "2. Top 10 Borrowed Books" << endl;
    cout << "3. Top 10 Newest Books" << endl;
    cout << "4. Exit" << endl;
    cout << "Please enter your choice: ";
}

void Ranking::start() {
    vector<BBook> bbooks;
    vector<RReader> rreaders;
    loadBorrowRecords(bbooks, rreaders);

    int choice;
    while (true) {
        menu();
        cin >> choice;
        switch (choice) {
            case 1:
                showTopReaders(rreaders);
                break;
            case 2:
                showTopBooks(bbooks);
                break;
            case 3:
                showNewestBooks();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}