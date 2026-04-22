#pragma once
#include <iostream>
#include <string>
using namespace std;

class User
{
private:
    string Name;
    string gender;
    int age;

public:
    User(string Name, string gender, int age);
    void setName(string Name);
    string getName() const;
    void setGender(string gender);
    string getGender() const;
    void setAge(int Age);
    int getAge() const;
};