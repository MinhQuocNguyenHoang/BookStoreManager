#include "Admin.hpp"

Admin::Admin(string Name, string gender, int age)
    : User(Name, gender, age) {}

string Admin::getAccount() const
{
    return account;
}

string Admin::getPassword() const
{
    return password;
}

bool Admin::login(string username, string pass) const
{
    if (username == this->account && pass == this->password)
    {
        return true;
    }
    return false;
}