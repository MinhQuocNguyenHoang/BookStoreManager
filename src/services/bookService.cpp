#include <bookServices.hpp>

void bookService::addBook(string id, string Name, string Type, float price, int stock)
{
    Book newBook(id, Name, Type, price, stock);
    books.push_back(newBook);
    cout << "=> Thong bao: Da them sach '" << Name << "' vao kho thanh cong!\n";
}

bool bookService::updateStock(string id, int additionalStock)
{
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].getId() == id)
        {
            int currentStock = books[i].getStock();
            books[i].setStock(currentStock + additionalStock);

            cout << "=> Cap nhat thanh cong! So luong moi cua kho: " << books[i].getStock() << "\n";
            return true; // Báo hiệu đã tìm thấy và cập nhật xong
        }
    }

    cout << "=> Loi: Khong tim thay sach co ma " << id << "!\n";
    return false;
}

bool bookService::deleteBook(string id)
{
    for (auto it = books.begin(); it != books.end(); ++it)
    {
        if (it->getId() == id)
        {
            books.erase(it); // Lệnh xóa phần tử khỏi mảng động
            cout << "=> Da xoa sach co ma '" << id << "' khoi he thong!\n";
            return true;
        }
    }

    cout << "=> Loi: Khong tim thay sach co ma " << id << " de xoa!\n";
    return false;
}

void bookService::displayAllBooks() const
{
    cout << "\n===== DANH SACH KHO SACH =====\n";
    if (books.empty())
    {
        cout << "Kho sach hien dang trong!\n";
        return;
    }

    for (int i = 0; i < books.size(); i++)
    {
        cout << "Ma: " << books[i].getId()
             << " | Ten: " << books[i].getName()
             << " | Loai: " << books[i].getType()
             << " | Gia: " << books[i].getPrice() << "$"
             << " | Ton kho: " << books[i].getStock() << "\n";
    }
    cout << "==============================\n";
}

void bookService::searchBookByTitle(std::string keyword) const
{
    string lowerKeyword = keyword;
    for (int i = 0; i < lowerKeyword.length(); i++)
    {
        lowerKeyword[i] = tolower(lowerKeyword[i]);
    }

    bool found = false;
    for (int i = 0; i < books.size(); i++)
    {

        // Lấy tên sách trong kho và cũng chuyển nó về chữ thường
        string lowerBookName = books[i].getName();
        for (int j = 0; j < lowerBookName.length(); j++)
        {
            lowerBookName[j] = tolower(lowerBookName[j]);
        }

        if (lowerBookName.find(lowerKeyword) != string::npos)
        {

            // In ra sách tìm được (vẫn in tên gốc viết hoa chữ cái đầu cho đẹp)
            cout << "- Ma: " << books[i].getId()
                 << " | Ten: " << books[i].getName()
                 << " | Loai: " << books[i].getType()
                 << " | Gia: " << books[i].getPrice() << "$"
                 << " | Ton kho: " << books[i].getStock() << "\n";

            found = true;
        }
    }

    if (found == false)
    {
        cout << "Khong co cuon sach nao chua tu khoá nay!\n";
    }
    cout << "=============================================\n";
}

Book *bookService::getBookById(string bookId)
{
    for (int i = 0; i < books.size(); i++)
    {
        // Nếu tìm thấy mã sách khớp với mã người dùng nhập
        if (books[i].getId() == bookId)
        {
            return &books[i]; // Trả về 'địa chỉ' của cuốn sách đó trong kho
        }
    }
    // Nếu duyệt hết kho mà không thấy, trả về con trỏ rỗng (nullptr)
    return nullptr;
}

void bookService::loadBooksFromFile(string filepath)
{
    ifstream file(filepath);
    if (!file.is_open())
    {
        cout << "=> Khoi tao kho sach moi (chua co file data).\n";
        return;
    }

    string line;
    books.clear(); // Xóa sạch kho cũ trước khi tải dữ liệu mới lên

    // Đọc từng dòng trong file
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, type, priceStr, stockStr;

        // Cắt dữ liệu bằng dấu phẩy ','
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, type, ',');
        getline(ss, priceStr, ',');
        getline(ss, stockStr, ',');

        if (!id.empty())
        {
            // Biến chữ thành số (stof: float, stoi: int) và đưa vào kho
            Book b(id, name, type, stof(priceStr), stoi(stockStr));
            books.push_back(b);
        }
    }
    file.close();
    cout << "=> Da tai xong du lieu tu file '" << filepath << "'!\n";
}

void bookService::saveBooksToFile(string filepath)
{
    ofstream file(filepath);
    for (int i = 0; i < books.size(); i++)
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