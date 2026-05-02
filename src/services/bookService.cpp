#include "bookServices.hpp"
#include <iostream>

// =====================================================
// ================= CRUD BOOK ==========================
// =====================================================

void bookService::addBook(const string &id, const string &Name,
                          const string &Type, float price, int stock)
{
    books.emplace_back(id, Name, Type, price, stock);
    cout << "=> Added book: " << Name << endl;
}

bool bookService::updateStock(const string &id, int additionalStock)
{
    for (auto &b : books)
    {
        if (b.getId() == id)
        {
            b.setStock(b.getStock() + additionalStock);
            return true;
        }
    }
    return false;
}

bool bookService::deleteBook(const string &id)
{
    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it->getId() == id)
        {
            books.erase(it);
            return true;
        }
    }
    return false;
}

// =====================================================
// ================= GET DATA ===========================
// =====================================================

vector<Book> &bookService::getAllBooks()
{
    return books;
}

Book *bookService::getBookById(const string &bookId)
{
    for (auto &b : books)
    {
        if (b.getId() == bookId)
            return &b;
    }
    return nullptr;
}

// =====================================================
// ================= SEARCH =============================
// =====================================================

vector<Book> bookService::searchBookByTitle(const string &keyword)
{
    vector<Book> result;

    string lowerKeyword = keyword;
    for (auto &c : lowerKeyword)
        c = tolower(c);

    for (auto &b : books)
    {
        string name = b.getName();
        for (auto &c : name)
            c = tolower(c);

        if (name.find(lowerKeyword) != string::npos)
            result.push_back(b);
    }

    return result;
}

// =====================================================
// ================= FILE I/O ===========================
// =====================================================

void bookService::loadFromFile(string filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        cout << "No data file found, starting empty.\n";
        return;
    }

    books.clear();
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, type, priceStr, stockStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, priceStr, ',');
        getline(ss, stockStr, ',');

        if (!id.empty())
        {
            books.emplace_back(id, name, type,
                               stof(priceStr), stoi(stockStr));
        }
    }

    file.close();
}

void bookService::saveToFile(string filepath)
{
    ofstream file(filepath);

    for (auto &b : books)
    {
        file << b.getId() << ","
             << b.getName() << ","
             << b.getType() << ","
             << b.getPrice() << ","
             << b.getStock() << "\n";
    }

    file.close();
}