#include <bookServices.hpp>

// =====================================================
// ================ NHÓM: CRUD BOOK ====================
// =====================================================

// ==========================================
// Function: addBook
// Mô tả: Thêm một cuốn sách mới vào kho
// Input:
//   - id: mã sách
//   - Name: tên sách
//   - Type: thể loại
//   - price: giá sách
//   - stock: số lượng ban đầu
// Output: void
// ==========================================
void bookService::addBook(string id, string Name, string Type, float price, int stock)
{
    Book newBook(id, Name, Type, price, stock);
    books.push_back(newBook);
    cout << "=> Thong bao: Da them sach '" << Name << "' vao kho thanh cong!\n";
}

// ==========================================
// Function: updateStock
// Mô tả: Cập nhật (cộng thêm) số lượng sách trong kho
// Input:
//   - id: mã sách cần cập nhật
//   - additionalStock: số lượng thêm vào
// Output:
//   - true: cập nhật thành công
//   - false: không tìm thấy sách
// ==========================================
bool bookService::updateStock(string id, int additionalStock)
{
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].getId() == id)
        {
            int currentStock = books[i].getStock();
            books[i].setStock(currentStock + additionalStock);

            cout << "=> Cap nhat thanh cong! So luong moi cua kho: " << books[i].getStock() << "\n";
            return true;
        }
    }

    cout << "=> Loi: Khong tim thay sach co ma " << id << "!\n";
    return false;
}

// ==========================================
// Function: deleteBook
// Mô tả: Xóa một cuốn sách khỏi kho theo id
// Input:
//   - id: mã sách cần xóa
// Output:
//   - true: xóa thành công
//   - false: không tìm thấy sách
// ==========================================
bool bookService::deleteBook(string id)
{
    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it->getId() == id)
        {
            books.erase(it);
            cout << "=> Da xoa sach co ma '" << id << "' khoi he thong!\n";
            return true;
        }
    }

    cout << "=> Loi: Khong tim thay sach co ma " << id << " de xoa!\n";
    return false;
}

// =====================================================
// ============== NHÓM: TRUY XUẤT DỮ LIỆU ==============
// =====================================================

// ==========================================
// Function: getAllBooks
// Mô tả: Lấy toàn bộ danh sách sách trong kho
// Input: none
// Output:
//   - reference tới vector<Book>
// Lưu ý: trả về reference để thao tác trực tiếp
// ==========================================
vector<Book> &bookService::getAllBooks()
{
    return books;
}

// ==========================================
// Function: getBookById
// Mô tả: Tìm sách theo mã id
// Input:
//   - bookId: mã sách cần tìm
// Output:
//   - con trỏ tới Book nếu tìm thấy
//   - nullptr nếu không tồn tại
// ==========================================
Book *bookService::getBookById(string bookId)
{
    for (size_t i = 0; i < books.size(); i++)
    {
        if (books[i].getId() == bookId)
        {
            return &books[i];
        }
    }
    return nullptr;
}

// =====================================================
// ============== NHÓM: TÌM KIẾM ========================
// =====================================================

// ==========================================
// Function: searchBookByTitle
// Mô tả: Tìm kiếm sách theo tên (không phân biệt hoa thường)
// Input:
//   - keyword: từ khóa tìm kiếm
// Output:
//   - vector<Book> chứa các sách phù hợp
// ==========================================
vector<Book> bookService::searchBookByTitle(string keyword)
{
    vector<Book> result;

    string lowerKeyword = keyword;
    for (auto &c : lowerKeyword)
        c = tolower(c);

    for (auto &book : books)
    {
        string name = book.getName();
        for (auto &c : name)
            c = tolower(c);

        if (name.find(lowerKeyword) != string::npos)
        {
            result.push_back(book);
        }
    }

    return result;
}

// =====================================================
// ============== NHÓM: FILE I/O ========================
// =====================================================

// ==========================================
// Function: loadBooksFromFile
// Mô tả: Đọc dữ liệu sách từ file CSV vào hệ thống
// Input:
//   - filepath: đường dẫn file
// Output: void
// ==========================================
void bookService::loadBooksFromFile(string filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        cout << "=> Khoi tao kho sach moi (chua co file data).\n";
        return;
    }

    string line;
    books.clear(); // Xóa dữ liệu cũ

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
            Book b(id, name, type, stof(priceStr), stoi(stockStr));
            books.push_back(b);
        }
    }

    file.close();
    cout << "=> Da tai xong du lieu tu file '" << filepath << "'!\n";
}

// ==========================================
// Function: saveBooksToFile
// Mô tả: Lưu toàn bộ dữ liệu sách ra file CSV
// Input:
//   - filepath: đường dẫn file
// Output: void
// ==========================================
void bookService::saveBooksToFile(string filepath)
{
    ofstream file(filepath);

    for (size_t i = 0; i < books.size(); i++)
    {
        file << books[i].getId() << ","
             << books[i].getName() << ","
             << books[i].getType() << ","
             << books[i].getPrice() << ","
             << books[i].getStock() << "\n";
    }

    file.close();
    cout << "=> Da luu du lieu an toan!\n";
}