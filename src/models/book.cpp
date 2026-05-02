#include "book.hpp"

// ================= CONSTRUCTOR =================
Book::Book(const string &id, const string &Name,
           const string &Type, float price, int stock)
    : id(id), Name(Name), Type(Type),
      price(price), stock(stock)
{
}

// ================= SETTER =================
void Book::setName(const string &Name)
{
    this->Name = Name;
}

void Book::setType(const string &Type)
{
    this->Type = Type;
}

void Book::setPrice(float price)
{
    this->price = price;
}

void Book::setStock(int stock)
{
    this->stock = stock;
}

void Book::setId(const string &id)
{
    this->id = id;
}

// ================= GETTER =================
string Book::getName() const
{
    return Name;
}

string Book::getType() const
{
    return Type;
}

float Book::getPrice() const
{
    return price;
}

int Book::getStock() const
{
    return stock;
}

string Book::getId() const
{
    return id;
}