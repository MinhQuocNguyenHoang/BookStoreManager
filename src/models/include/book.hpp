#pragma once
#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
    string id;
    string Name;
    string Type;
    float price;
    int stock;

public:
    Book(string id, string Name, string Type, float price, int stock);

    void setName(string Name);

    string getName() const;

    void setType(string Type);

    string getType() const;

    void setPrice(float Type);

    float getPrice() const;

    void setStock(int stock);

    int getStock() const;

    void setId(string id);
    string getId() const;
};