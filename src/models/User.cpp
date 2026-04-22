#include <User.hpp>

User::User(string Name, string gender, int age)
{
    this->Name = Name;
    this->gender = gender;
    this->age = age;
}

void User::setName(string Name)
{
    this->Name = Name;
}

void User::setGender(string gender)
{
    this->gender = gender;
}

void User::setAge(int Age)
{
    this->age = Age;
}

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