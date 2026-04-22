#include "Admin.hpp"

Admin::Admin(string Name, string gender, int age)
    : User(Name, gender, age) {}

string getAccount() const {
    return account;
}

int getPassword() const {
    return password;
}