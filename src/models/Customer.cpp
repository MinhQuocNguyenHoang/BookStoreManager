#include <Customer.hpp>

Customer::Customer(string Name, string gender, int age) : User(Name, gender, age) {};

void Customer::setPhone(int phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

int Customer::getPhone() const
{
    return phoneNumber;
}
