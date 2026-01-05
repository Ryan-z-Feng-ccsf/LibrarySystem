# Library Management System (C++)

> 🎓 **Course Project**: Computer Programming (Dec 2023)
> 📅 **Date**: December 2023

A robust, console-based Library Management System developed in C++. This application handles book inventory, reader management, and borrowing records using file-based persistence.

## 👨‍💻 Project Background & Contribution

This project was developed as a group assignment for the **Computer Programming** course.

**My Key Contributions:**
* **Search Engine (`Find` Module)**: Designed and implemented the core search logic, allowing users to find books by Title, Author, Publisher, or ISBN with fuzzy matching support.
* **Admin Management (`Admin` Module)**: Developed the full **CRUD (Create, Read, Update, Delete)** functionality for the book inventory, enabling administrators to manage the library database efficiently.

## 🚀 Features

* **Smart Search**: Find books by Title, Author, Publisher, or ISBN (supports spaces in keywords).
* **Inventory Control**: Real-time updates of book stock when books are borrowed or returned.
* **Role Management**: Distinct functionalities for **Admins** (Book Management) and **Readers** (Borrowing/Returning).
* **Data Persistence**: Uses text files (`.txt`) to permanently store data, ensuring records are saved between sessions.

## 🛠️ Tech Stack

* **Language**: C++ (Standard 11/14/17)
* **Build System**: CMake
* **IDE**: CLion
* **Data Handling**: File I/O with Tab-Separated Values (TSV) to handle complex string inputs.

## 🔧 How to Run

1.  **Clone the repository**:
    ```bash
    git clone [https://github.com/YOUR_USERNAME/LibrarySystem.git](https://github.com/YOUR_USERNAME/LibrarySystem.git)
    ```
2.  **Open in CLion** (or compile via CMake).
3.  **Build & Run**.
    * *Note: Ensure the `data/` folder is in the working directory so the program can load the databases.*

## 📝 Usage Guide

1.  **For Admins**: Log in to access the **Book Management Menu**. You can add new books, update existing stock/info, or delete obsolete records.
2.  **For Readers**: Use the **Search** function to find books and proceed to **Borrow** or **Return** using the Book ID.

## 📂 Project Structure

The project follows a modular C++ structure separating logic, headers, and data.

```text
├── data/
│   ├── books.txt              # Main book database
│   ├── borrowing_history.txt  # Logs of all transactions
│   ├── content.txt            # Detailed descriptions of books
│   └── readers.txt            # Registered reader accounts
├── include/                   # Header files (.h)
│   ├── Admin.h
│   ├── Book.h
│   ├── BorrowReturn.h
│   ├── Find.h
│   ├── Ranking.h
│   ├── Reader.h
│   └── User.h
├── src/                       # Source files (.cpp)
│   ├── Admin.cpp              # Admin logic (Add/Delete/Update books)
│   ├── Book.cpp
│   ├── BorrowReturn.cpp
│   ├── Find.cpp               # Search implementation
│   ├── Ranking.cpp
│   └── Reader.cpp
├── CMakeLists.txt
└── main.cpp                   # Entry point
