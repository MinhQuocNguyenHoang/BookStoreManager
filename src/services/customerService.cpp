#include <customerServices.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// =====================================================
// ================ NHÓM: CRUD CUSTOMER ================
// =====================================================

// ==========================================
// Function: addCustomer
// Mô tả: Thêm một khách hàng mới vào danh sách
// Input:
//   - id: mã khách hàng
//   - name: tên khách hàng
//   - gender: giới tính
//   - phone: số điện thoại
// Output: void
// ==========================================
void customerService::addCustomer(string id, string name, string gender, string phone)
{
    Customer c(id, name, gender, phone);
    customers.push_back(c);

    cout << "=> Da them khach hang: " << name << endl;
}

// =====================================================
// ============== NHÓM: TRUY XUẤT DỮ LIỆU ==============
// =====================================================

// ==========================================
// Function: getAllCustomers
// Mô tả: Lấy toàn bộ danh sách khách hàng
// Input: none
// Output:
//   - vector<Customer>: bản sao danh sách khách hàng
// Lưu ý: trả về bản sao nên không ảnh hưởng dữ liệu gốc
// ==========================================
vector<Customer> customerService::getAllCustomers() const
{
    return customers;
}

// =====================================================
// ============== NHÓM: FILE I/O ========================
// =====================================================

// ==========================================
// Function: loadCustomersFromFile
// Mô tả: Đọc dữ liệu khách hàng từ file CSV
// Input:
//   - filepath: đường dẫn file
// Output: void
// ==========================================
void customerService::loadCustomersFromFile(string filepath)
{
    ifstream file(filepath);

    if (!file.is_open())
    {
        cout << "=> Chua co file customer\n";
        return;
    }

    customers.clear(); // Xóa dữ liệu cũ trước khi load

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string id, name, gender, phone;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, gender, ',');
        getline(ss, phone, ',');

        Customer c(id, name, gender, phone);
        customers.push_back(c);
    }

    file.close();
}

// ==========================================
// Function: saveCustomersToFile
// Mô tả: Lưu danh sách khách hàng ra file CSV
// Input:
//   - filepath: đường dẫn file
// Output: void
// ==========================================
void customerService::saveCustomersToFile(string filepath)
{
    ofstream file(filepath);

    for (auto &c : customers)
    {
        file << c.getId() << ","
             << c.getName() << ","
             << c.getGender() << ","
             << c.getPhone() << "\n";
    }

    file.close();
}