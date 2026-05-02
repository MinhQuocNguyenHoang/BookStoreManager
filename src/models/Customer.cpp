#include "Customer.hpp"

// ================= CONSTRUCTOR =================
Customer::Customer() {}

Customer::Customer(const string &id, const string &name,
                   const string &gender, const string &phone)
    : id(id), name(name), gender(gender), phone(phone)
{
}

// ================= GETTER =================
string Customer::getId() const { return id; }
string Customer::getName() const { return name; }
string Customer::getGender() const { return gender; }
string Customer::getPhone() const { return phone; }

// ================= SETTER =================
void Customer::setId(const string &id)
{
    this->id = id;
}

void Customer::setName(const string &name)
{
    this->name = name;
}

void Customer::setGender(const string &gender)
{
    this->gender = gender;
}

void Customer::setPhone(const string &phone)
{
    this->phone = phone;
}