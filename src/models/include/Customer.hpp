#pragma once
#include <string>

class Customer
{
private:
    std::string id;
    std::string name;
    std::string gender;
    std::string phone;

public:
    Customer();
    Customer(std::string id, std::string name, std::string gender, std::string phone);

    std::string getId() const;
    std::string getName() const;
    std::string getGender() const;
    std::string getPhone() const;
};