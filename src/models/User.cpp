#include "User.hpp"

// ================= CONSTRUCTOR =================
User::User(const string &Name, const string &gender, int age)
    : Name(Name), gender(gender), age(age)
{
}

// ================= SETTER =================
void User::setName(const string &Name)
{
    this->Name = Name;
}

void User::setGender(const string &gender)
{
    this->gender = gender;
}

void User::setAge(int age)
{
    this->age = age;
}

// ================= GETTER =================
string User::getName() const
{
    return Name;
}

string User::getGender() const
{
    return gender;
}

int User::getAge() const
{
    return age;
}

// ================= BEHAVIOR =================
void User::displayInfo() const
{
    cout << "Name: " << Name
         << " | Gender: " << gender
         << " | Age: " << age << endl;
}

// ================= POLYMORPHISM =================
string User::getRole() const
{
    return "User";
}