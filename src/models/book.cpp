#include <book.hpp>

Book::Book(string Name, string Type, float price, int stock)
{
    this->Name = Name;
    this->Type = Type;
    this->price = price;
    this->stock = stock;
}

void Book::setName(string Name)
{
    this->Name = Name;
}

string Book::getName() const
{
    return Name;
}

void Book::setPrice(float price)
{
    this->price = price;
}

float Book::getPrice() const
{
    return price;
}

void Book::setType(string Type)
{
    this->Type = Type;
}

string Book::getType() const
{
    return Type;
}

void Book::setStock(int stock)
{
    this->stock = stock;
}

int Book::getStock() const
{
    return stock;
}

string Book::getId() const
{
    return id;
}

void Book::setId(string id)
{
    this->id = id;
}