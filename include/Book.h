//
// Created by Zhuolei on 1/5/2026.
//

#ifndef LIBRARYMANAGEMENT_BOOK_H
#define LIBRARYMANAGEMENT_BOOK_H
#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    string id;
    string ISBN;
    string name;
    string author;
    string publisher;
    string date;
    float price;
    int quantity;
    int borrowCount;

    Book() : price(0), quantity(0), borrowCount(0) {}

    Book(string i, int count, string I, string n, string a, string per, string d, float p, int q)
            : id(i), borrowCount(count), ISBN(I), name(n), author(a), publisher(per), date(d), price(p), quantity(q) {}

    string getId() const;

    string getName() const;
    string getDate() const;
    int getBorrowCount() const ;
    void increaseBorrowCount() ;

    void print() const ;

};



#endif //LIBRARYMANAGEMENT_BOOK_H
