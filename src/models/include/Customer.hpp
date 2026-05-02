#pragma once
#include <string>
using namespace std;

class Customer
{
private:
    string id;
    string name;
    string gender;
    string phone;

public:
    // Constructor
    Customer();
    Customer(const string &id, const string &name,
             const string &gender, const string &phone);

    // Getter
    string getId() const;
    string getName() const;
    string getGender() const;
    string getPhone() const;

    // Setter (thêm để chuẩn OOP)
    void setId(const string &id);
    void setName(const string &name);
    void setGender(const string &gender);
    void setPhone(const string &phone);
};