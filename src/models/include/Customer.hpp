#pragma once
#include <string>
using namespace std;

#include "User.hpp"

class Customer : public User
{
private:
    int phoneNumber;

public:
    Customer(string Name, string gender, int age);

    void setPhone(int phoneNumber);
    int getPhone() const;
};