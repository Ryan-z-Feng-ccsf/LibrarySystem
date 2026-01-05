//
// Created by Zhuolei on 1/5/2026.
//

#ifndef LIBRARYMANAGEMENT_FIND_H
#define LIBRARYMANAGEMENT_FIND_H

#include "Book.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Find {
public:
    void searchByName();

    void searchByAuthor();

    void searchByPublisher();

    void searchByISBN();

    void menu();

    void start();

private:


    void displayContent(const string &bookId);

    string toLower(string s);
};


#endif //LIBRARYMANAGEMENT_FIND_H
