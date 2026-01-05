//
// Created by Zhuolei on 1/5/2026.
//

#include "../include/Find.h"
#include "../include/Find.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

#include "../include/Find.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits> // For numeric_limits
#include <vector>
#include <iostream>

using namespace std;

string Find::toLower(string s) {
    string res = s;
    for (char &c: res) {
        c = tolower(c);
    }
    return res;
}

// --- Utility function: Reads data/content.txt and displays detailed contents ---
void Find::displayContent(const string &targetId) {
    ifstream file("data/content.txt");
    if (!file) {
        cout << "Error: Unable to open data/content.txt" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        ss >> id; // Read the ID at the beginning of the line

        if (id == targetId) {
            string content;
            getline(ss, content); // Read the remainder

            cout << "\n==============================================" << endl;
            cout << " [ Book Content / Description ]" << endl;
            cout << " ID: " << id << endl;

            size_t first = content.find_first_not_of(" \t");
            if (string::npos != first) {
                cout << " Detail: " << content.substr(first) << endl;
            } else {
                cout << " Detail: " << content << endl;
            }
            cout << "==============================================\n" << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No content description found for Book ID: " << targetId << endl;
    }
    file.close();
}

// --- General Parsing and Search Logic ---
// To minimize code duplication, the four search functions share identical parsing logic, differing only in their condition checks.
// The specific implementation for each function is shown here.

// --- 1. Search by Book Title ---
void Find::searchByName() {
    string keyword;
    cout << "Enter book name keyword: ";
    cin.ignore();
    getline(cin, keyword);

    ifstream file("data/books.txt");
    if (!file) {
        cout << "Unable to open data/books.txt" << endl;
        return;
    }

    string line;
    vector<string> foundIds;
    bool found = false;

    cout << "\n---------------- Search Results ----------------" << endl;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream iss(line);
        string id, ISBN, name, author, publisher, date, priceStr, qtyStr;
        float price;
        int quantity;

        // 【Key Modification】: Use `getline` exclusively with the '\t' delimiter.
        getline(iss, id, '\t');
        getline(iss, ISBN, '\t');
        getline(iss, name, '\t');
        getline(iss, author, '\t');
        getline(iss, publisher, '\t');
        getline(iss, date, '\t');

        getline(iss, priceStr, '\t');
        price = stof(priceStr); // Convert string to floating-point number

        getline(iss, qtyStr, '\t');
        quantity = stoi(qtyStr); // String to Integer

        // Logic: Direct lookup, no need to replace underscores with spaces anymore.
        if (toLower(name).find(toLower(keyword)) != string::npos) {
            Book b(id, 0, ISBN, name, author, publisher, date, price, quantity);
            b.print();
            foundIds.push_back(id);
            found = true;
        }
    }
    file.close();

    if (!found) {
        cout << "No books found matching the keyword." << endl;
        return;
    }

    cout << "------------------------------------------------" << endl;

    // Interactive Section
    while (true) {
        cout << "Enter Book ID to view content (or '0' to return): ";
        string choiceId;
        cin >> choiceId;
        if (choiceId == "0") break;

        bool isValid = false;
        for (const string &fid: foundIds) {
            if (fid == choiceId) isValid = true;
        }

        if (isValid) displayContent(choiceId);
        else cout << "ID not found in the search results above." << endl;
    }
}

// --- 2. Search by Author ---
void Find::searchByAuthor() {
    string keyword;
    cout << "Enter author name keyword: ";
    cin.ignore();
    getline(cin, keyword);

    ifstream file("data/books.txt");
    if (!file) {
        cout << "Unable to open data/books.txt" << endl;
        return;
    }

    string line;
    vector<string> foundIds;
    bool found = false;

    cout << "\n---------------- Search Results ----------------" << endl;

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream iss(line);
        string id, ISBN, name, author, publisher, date, priceStr, qtyStr;
        float price;
        int quantity;

        getline(iss, id, '\t');
        getline(iss, ISBN, '\t');
        getline(iss, name, '\t');
        getline(iss, author, '\t');
        getline(iss, publisher, '\t');
        getline(iss, date, '\t');
        getline(iss, priceStr, '\t');
        price = stof(priceStr);
        getline(iss, qtyStr, '\t');
        quantity = stoi(qtyStr);

        // 【Critical Fix】: This was originally named "name," but has now been changed to "author."
        if (toLower(author).find(toLower(keyword)) != string::npos) {
            Book b(id, 0, ISBN, name, author, publisher, date, price, quantity);
            b.print();
            foundIds.push_back(id);
            found = true;
        }
    }
    file.close();

    if (!found) {
        cout << "No books found matching the keyword." << endl;
        return;
    }
    cout << "------------------------------------------------" << endl;
    // (Omitted duplicate interaction code; logic remains the same)
    while (true) {
        cout << "Enter Book ID to view content (or '0' to return): ";
        string choiceId;
        cin >> choiceId;
        if (choiceId == "0") break;
        bool isValid = false;
        for (const string &fid: foundIds) if (fid == choiceId) isValid = true;
        if (isValid) displayContent(choiceId);
        else cout << "ID not found in results." << endl;
    }
}

// --- 3. Search by Publisher ---
void Find::searchByPublisher() {
    string keyword;
    cout << "Enter publisher keyword: ";
    cin.ignore();
    getline(cin, keyword);

    ifstream file("data/books.txt");
    if (!file) {
        cout << "Unable to open data/books.txt" << endl;
        return;
    }

    string line;
    vector<string> foundIds;
    bool found = false;

    cout << "\n---------------- Search Results ----------------" << endl;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream iss(line);
        string id, ISBN, name, author, publisher, date, priceStr, qtyStr;
        float price;
        int quantity;

        getline(iss, id, '\t');
        getline(iss, ISBN, '\t');
        getline(iss, name, '\t');
        getline(iss, author, '\t');
        getline(iss, publisher, '\t');
        getline(iss, date, '\t');
        getline(iss, priceStr, '\t');
        price = stof(priceStr);
        getline(iss, qtyStr, '\t');
        quantity = stoi(qtyStr);

        if (toLower(publisher).find(toLower(keyword)) != string::npos) {
            Book b(id, 0, ISBN, name, author, publisher, date, price, quantity);
            b.print();
            foundIds.push_back(id);
            found = true;
        }
    }
    file.close();

    if (!found) {
        cout << "No books found matching the keyword." << endl;
        return;
    }
    cout << "------------------------------------------------" << endl;
    while (true) {
        cout << "Enter Book ID to view content (or '0' to return): ";
        string choiceId;
        cin >> choiceId;
        if (choiceId == "0") break;
        bool isValid = false;
        for (const string &fid: foundIds) if (fid == choiceId) isValid = true;
        if (isValid) displayContent(choiceId);
        else cout << "ID not found in results." << endl;
    }
}

// --- 4. Search by ISBN ---
void Find::searchByISBN() {
    string keyword;
    cout << "Enter ISBN: ";
    cin.ignore();
    getline(cin, keyword);

    ifstream file("data/books.txt");
    if (!file) {
        cout << "Unable to open data/books.txt" << endl;
        return;
    }

    string line;
    vector<string> foundIds;
    bool found = false;

    cout << "\n---------------- Search Results ----------------" << endl;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream iss(line);
        string id, ISBN, name, author, publisher, date, priceStr, qtyStr;
        float price;
        int quantity;

        getline(iss, id, '\t');
        getline(iss, ISBN, '\t');
        getline(iss, name, '\t');
        getline(iss, author, '\t');
        getline(iss, publisher, '\t');
        getline(iss, date, '\t');
        getline(iss, priceStr, '\t');
        price = stof(priceStr);
        getline(iss, qtyStr, '\t');
        quantity = stoi(qtyStr);

        if (ISBN == keyword) {
            Book b(id, 0, ISBN, name, author, publisher, date, price, quantity);
            b.print();
            foundIds.push_back(id);
            found = true;
        }
    }
    file.close();

    if (!found) {
        cout << "No books found with this ISBN." << endl;
        return;
    }
    cout << "------------------------------------------------" << endl;
    while (true) {
        cout << "Enter Book ID to view content (or '0' to return): ";
        string choiceId;
        cin >> choiceId;
        if (choiceId == "0") break;
        bool isValid = false;
        for (const string &fid: foundIds) if (fid == choiceId) isValid = true;
        if (isValid) displayContent(choiceId);
        else cout << "ID not found in results." << endl;
    }
}

// Menu
void Find::menu() {
    cout << "\n====== Search Menu ======" << endl;
    cout << "1. Search by Book Name" << endl;
    cout << "2. Search by Author" << endl;
    cout << "3. Search by Publisher" << endl;
    cout << "4. Search by ISBN" << endl;
    cout << "5. Exit" << endl;
    cout << "Please enter your choice: ";
}

// Start
void Find::start() {
    int choice;
    while (true) {
        menu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                searchByName();
                break;
            case 2:
                searchByAuthor();
                break;
            case 3:
                searchByPublisher();
                break;
            case 4:
                searchByISBN();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }
}