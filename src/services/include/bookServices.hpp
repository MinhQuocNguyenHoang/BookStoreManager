#pragma once
#include <book.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <Admin.hpp>
class bookService
{
private:
    vector<Book> books;

public:
    void addBook(string id, string Name, string Type, float price, int stock);
    bool updateStock(string id, int additionalStock);
    bool deleteBook(string id);
    vector<Book> &getAllBooks();
    vector<Book> searchBookByTitle(std::string keyword);
    Book *getBookById(std::string bookId);
    void loadBooksFromFile(string filepath);
    void saveBooksToFile(string filepath);
};