//
// Created by Zhuolei on 1/5/2026.
//

#include "../include/Book.h"

void Book::print() const {
    cout << "ID: " << id << endl;
    cout << "ISBN/ISSN: " << ISBN << endl;
    cout << "Name: " << name << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Date: " << date << endl;
    cout << "Price: " << price << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Borrowed Times: " << borrowCount << endl;
    cout << "---------------------------" << endl;

}

void Book::increaseBorrowCount() {
    borrowCount++;

}

int Book::getBorrowCount() const {
    return borrowCount;
}

string Book::getName() const {
    return name;
}

string Book::getId() const {
    return id;
}

string Book::getDate() const {
    return date;
}
