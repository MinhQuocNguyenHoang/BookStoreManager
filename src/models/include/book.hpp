#pragma once
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
    // Constructor
    Book(const string &id, const string &Name,
         const string &Type, float price, int stock);

    // Setter
    void setName(const string &Name);
    void setType(const string &Type);
    void setPrice(float price);
    void setStock(int stock);
    void setId(const string &id);

    // Getter
    string getName() const;
    string getType() const;
    float getPrice() const;
    int getStock() const;
    string getId() const;
};