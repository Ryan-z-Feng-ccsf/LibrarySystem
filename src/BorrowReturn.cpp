//
// Created by Zhuolei on 1/5/2026.
//

#include "../include/BorrowReturn.h"

void BorrowReturn::loadInformation() {
    // Reader Information
    ifstream readerFile("data/readers.txt");
    if (!readerFile) {
        cerr << "Unable to open readers.txt" << endl;
        return;
    }
    string account, password;
    while (readerFile >> account >> password) {
        readers.push_back(Reader(account, password));
    }
    readerFile.close();

    // Book Information (Optional)
    ifstream bookFile("data/books.txt");
    if (!bookFile) return;
    string line;
    while (getline(bookFile, line)) {
        // Here, each line can be parsed into a Book object, if needed.
    }
    bookFile.close();
}

void BorrowReturn::saveBorrowingHistory(const string &account, const string &bookId) {
    ofstream outFile(borrowingHistoryFile, ios::app);
    if (!outFile) {
        cerr << "Unable to open borrowing_history.txt" << endl;
        return;
    }
    outFile << account << " " << bookId << endl;
}

vector<pair<string, string>> BorrowReturn::loadBorrowingHistory() {
    vector<pair<string, string>> history;
    ifstream inFile(borrowingHistoryFile);
    if (!inFile) return history;

    string account, bookId;
    while (inFile >> account >> bookId) {
        history.push_back({account, bookId});
    }
    inFile.close();
    return history;
}

Reader *BorrowReturn::findReader(const string &account) {
    for (Reader &r: readers) {
        if (r.getAccount() == account)
            return &r;
    }
    return nullptr;
}

void BorrowReturn::borrowBook() {
    string account, bookId;
    cout << "account:";
    cin >> account;
    cout << "enter book ID:";
    cin >> bookId;

    Reader *reader = findReader(account);
    if (!reader) {
        cout << "Invalid account!" << endl;
        return;
    }

    reader->borrowBook(bookId);
    saveBorrowingHistory(account, bookId);

    cout << "Book borrowing successful!" << endl;
}

void BorrowReturn::returnBook() {
    string account, bookId;
    cout << "account:";
    cin >> account;
    cout << "enter book ID:";
    cin >> bookId;

    Reader *reader = findReader(account);
    if (!reader) {
        cout << "Invalid account!" << endl;
        return;
    }

    reader->returnBook(bookId);
    cout << "Book returning successful!" << endl;
}

void BorrowReturn::viewBorrowingHistory() {
    string account;
    cout << "account:";
    cin >> account;

    Reader *reader = findReader(account);
    if (!reader) {
        cout << "invalid account!" << endl;
        return;
    }

    reader->viewBorrowingHistory();
}

void BorrowReturn::menu() {
    cout << "\n====== Borrow & Return Menu ======" << endl;
    cout << "1. Borrow Book" << endl;
    cout << "2. Return Book" << endl;
    cout << "3. View Borrowing History" << endl;
    cout << "4. Exit" << endl;
    cout << "Please enter your choice: ";
}

void BorrowReturn::start() {
    loadInformation();
    int choice;
    while (true) {
        menu();
        cin >> choice;
        switch (choice) {
            case 1:
                borrowBook();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                viewBorrowingHistory();
                break;
            case 4:
                return;
            default:
                cout << "invalid option! Enter again!" << endl;
                break;
        }
    }
}