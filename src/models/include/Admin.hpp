#pragma once
#include <string>
using namespace std;

#include "User.hpp"

class Admin : public User
{
private:
string account = "Nhom4";
int password = "12345";
public:
    Admin(string Name, string gender, int age);
    string getAccount() const ;
    int getPassword() const ;
};