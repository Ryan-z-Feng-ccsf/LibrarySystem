//
// Created by Zhuolei on 1/5/2026.
//

#include "../include/Admin.h"
#include <limits>

const string BOOKS_FILE = "data/books.txt";

// --- Menu and Main Logic ---
void Admin::adminMenu() {
    cout << "\n====== Admin Menu ======" << endl;
    cout << "1. Manage Readers" << endl;
    cout << "2. Manage Books (Add/Delete/Update)" << endl;
    cout << "3. View Rankings" << endl;
    cout << "4. Find Books" << endl;
    cout << "5. Exit" << endl;
    cout << "Please enter your choice: ";
}

void Admin::start() {
    int choice;
    while (true) {
        adminMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1:
                manageReaders();
                break;
            case 2:
                manageBooks();
                break; // Enter the Book Management submenu
            case 3:
                viewRanking();
                break;
            case 4:
                findBooks();
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice. Try again." << endl;
                break;
        }
    }
}

// --- Book Management Subsystem ---
void Admin::manageBooks() {
    vector<Book> books;
    loadBooks(books); // Load data before entering the menu

    int choice;
    while (true) {
        cout << "\n--- Book Management ---\n";
        cout << "1. Add Book\n";
        cout << "2. Delete Book\n";
        cout << "3. Update Book\n";
        cout << "4. Save & Return to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                deleteBook(books);
                break;
            case 3:
                updateBook(books);
                break;
            case 4:
                saveBooks(books); // Save before exiting
                return;
            default:
                cout << "Invalid option.\n";
        }
    }
}

// --- File I/O Utility Functions ---
void Admin::loadBooks(vector<Book> &books) {
    books.clear();
    ifstream fin(BOOKS_FILE);
    if (!fin) return; // If the file doesn't exist, so be it.

    string id, ISBN, name, author, publisher, date;
    float price;
    int quantity;
    // Note: The reading logic here must perfectly match the format in your file.
    // Assuming the file format is: id ISBN name author publisher date price quantity
    // If your file stores borrowCount, it must also be read here.

    // Here, a simple sequential reading approach is adopted.
    // Your Book constructor: Book(string i, int count, string I, string n, string a, string per, string d, float p, int q)
    while (fin >> id >> ISBN >> name >> author >> publisher >> date >> price >> quantity) {
        // Assuming borrowCount hasn't been saved in the file yet, we default it to 0.
        // If your books.txt format is complex (e.g., book titles with spaces), it's recommended to use getline to handle it.
        books.push_back(Book(id, 0, ISBN, name, author, publisher, date, price, quantity));
    }
    fin.close();
}

void Admin::saveBooks(const vector<Book> &books) {
    ofstream fout(BOOKS_FILE);
    if (!fout) {
        cerr << "Error: Unable to open " << BOOKS_FILE << " for writing.\n";
        return;
    }
    for (const auto &book: books) {
        // Maintain consistent formatting by using tabs or spaces to separate elements.
        fout << book.id << " "
             << book.ISBN << " "
             << book.name << " "
             << book.author << " "
             << book.publisher << " "
             << book.date << " "
             << book.price << " "
             << book.quantity << endl;
    }
    fout.close();
    cout << "Changes saved to file successfully.\n";
}

// --- Specific Function Implementation ---

void Admin::addBook(vector<Book> &books) {
    string id, ISBN, name, author, publisher, date;
    float price;
    int quantity;

    cout << "Enter Book ID: ";
    cin >> id;

    // Check for duplicate IDs
    for (const auto &b: books) {
        if (b.id == id) {
            cout << "Error: Book ID already exists!\n";
            return;
        }
    }

    cin.ignore(); // Clear the buffer
    cout << "Enter ISBN: ";
    getline(cin, ISBN);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Publisher: ";
    getline(cin, publisher);
    cout << "Enter Date: ";
    getline(cin, date);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Quantity: ";
    cin >> quantity;

    // Create a new book with a default borrow count of 0.
    books.push_back(Book(id, 0, ISBN, name, author, publisher, date, price, quantity));
    cout << "Book added (in memory). Remember to Save & Return.\n";
}

void Admin::deleteBook(vector<Book> &books) {
    string id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    bool found = false;
    for (auto it = books.begin(); it != books.end();) {
        if (it->id == id) {
            it = books.erase(it);
            found = true;
            cout << "Book deleted.\n";
            // Do not break, to prevent duplicate IDs (though theoretically, this shouldn't occur).
        } else {
            ++it;
        }
    }
    if (!found) cout << "Book ID not found.\n";
}

void Admin::updateBook(vector<Book> &books) {
    string id;
    cout << "Enter Book ID to update: ";
    cin >> id;

    bool found = false;
    for (auto &book: books) {
        if (book.id == id) {
            cout << "Updating Book: " << book.name << endl;
            cin.ignore();
            cout << "New ISBN (Old: " << book.ISBN << "): ";
            getline(cin, book.ISBN);
            cout << "New Name (Old: " << book.name << "): ";
            getline(cin, book.name);
            cout << "New Author: ";
            getline(cin, book.author);
            cout << "New Publisher: ";
            getline(cin, book.publisher);
            cout << "New Date: ";
            getline(cin, book.date);
            cout << "New Price: ";
            cin >> book.price;
            cout << "New Quantity: ";
            cin >> book.quantity;
            found = true;
            cout << "Book updated.\n";
            break;
        }
    }
    if (!found) cout << "Book ID not found.\n";
}


// other stub functions remain unchanged.
void Admin::manageReaders() {
    cout << "[Admin] Manage Readers - Feature not implemented yet." << endl;
}

void Admin::viewRanking() {
    Ranking r;
    r.start();
}

void Admin::findBooks() {
    Find f;
    f.start();
}