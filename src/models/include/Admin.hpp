#pragma once
#include <string>
using namespace std;

#include "User.hpp"

class Admin : public User
{
private:
    string account = "admin123";
    string password = "FETEL30";

public:
    Admin(string Name, string gender, int age);
    string getAccount() const;
    string getPassword() const;
    bool login(string usernam, string pass) const;
};