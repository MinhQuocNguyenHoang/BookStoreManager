#pragma once
#include <string>
#include <iostream>
using namespace std;

class User
{
protected:
    string Name;
    string gender;
    int age;

public:
    // Constructor
    User(const string &Name, const string &gender, int age);

    // Setter
    void setName(const string &Name);
    void setGender(const string &gender);
    void setAge(int age);

    // Getter
    string getName() const;
    string getGender() const;
    int getAge() const;

    // Behavior
    void displayInfo() const;

    // Polymorphism
    virtual string getRole() const;
};
