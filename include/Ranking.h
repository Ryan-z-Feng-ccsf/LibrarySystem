//
// Created by Zhuolei on 1/5/2026.
//

#ifndef LIBRARYMANAGEMENT_RANKING_H
#define LIBRARYMANAGEMENT_RANKING_H


#include "Reader.h"
#include "Book.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct BBook {
    string id;
    int borrowCount;
};

struct RReader {
    string account;
    int borrowCount;
};

class Ranking {
public:
    void loadBorrowRecords(vector<BBook> &bbooks, vector<RReader> &rreaders);

    void showTopReaders(const vector<RReader> &rreaders);

    void showTopBooks(const vector<BBook> &bbooks);

    void showNewestBooks();

    void menu();

    void start();

private:


};


#endif //LIBRARYMANAGEMENT_RANKING_H
