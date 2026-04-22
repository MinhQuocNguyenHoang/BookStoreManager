#pragma once
#include <book.hpp>
#include <vector>
#include <fstream>
#include <sstream>

class bookService
{
private:
    vector<Book> books;

public:
    void addBook(string id, string Name, string Type, float price, int stock);
    void updateStock(string id, int additionalStock);
    void deleteBook(string id);
    void displayAllBooks() const;
    void searchBookByTitle(std::string keyword) const;
    Book *getBookById(std::string bookId);
    void loadBooksFromFile(string filepath);
    void saveBooksToFile(string filepath);
};