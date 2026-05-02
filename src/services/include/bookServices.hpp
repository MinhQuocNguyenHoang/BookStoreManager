#pragma once
#include "book.hpp"
#include "IService.hpp"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class bookService : public IService
{
private:
    vector<Book> books;

public:
    // CRUD
    void addBook(const string &id, const string &Name,
                 const string &Type, float price, int stock);

    bool updateStock(const string &id, int additionalStock);
    bool deleteBook(const string &id);

    // Getter
    vector<Book> &getAllBooks();
    vector<Book> searchBookByTitle(const string &keyword);
    Book *getBookById(const string &bookId);

    // File (đa hình từ IService)
    void loadFromFile(string filepath) override;
    void saveToFile(string filepath) override;
};