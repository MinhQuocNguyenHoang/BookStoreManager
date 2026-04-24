#include <Customer.hpp>

Customer::Customer() {}

Customer::Customer(std::string id, std::string name, std::string gender, std::string phone)
{
    this->id = id;
    this->name = name;
    this->gender = gender;
    this->phone = phone;
}

std::string Customer::getId() const { return id; }
std::string Customer::getName() const { return name; }
std::string Customer::getGender() const { return gender; }
std::string Customer::getPhone() const { return phone; }