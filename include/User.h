//
// Created by Zhuolei on 1/5/2026.
//

#ifndef LIBRARYMANAGEMENT_USER_H
#define LIBRARYMANAGEMENT_USER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class User {
public:
    string account;   // account
    string password;  // password
    int role;         // User Role (1=admin, 2=reader)

    // Constructor
    User(const string &acc, const string &pwd, int r)
            : account(acc), password(pwd), role(r) {}

    // Pure virtual function: Display user information
    virtual void display() = 0;

    // Verify Password
    bool checkPassword(const string &pwd) const {
        return password == pwd;
    }

    // Obtain Character
    int getRole() const {
        return role;
    }

    // Virtual destructors ensure proper destruction of derived classes.
    virtual ~User() = default;

};


#endif //LIBRARYMANAGEMENT_USER_H
