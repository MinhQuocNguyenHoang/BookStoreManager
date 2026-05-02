#pragma once
#include <string>
using namespace std;

#include "User.hpp"

class Admin : public User
{
private:
    string account;
    string password;

public:
    // Constructor
    Admin(const string &Name, const string &gender, int age,
          const string &account = "admin",
          const string &password = "123");

    // Getter
    string getAccount() const;
    string getPassword() const;

    // Setter
    void setAccount(const string &acc);
    void setPassword(const string &pass);

    // Login
    bool login(const string &username, const string &pass) const;

    // Polymorphism
    string getRole() const override;
};