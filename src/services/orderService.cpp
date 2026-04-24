#include "orderServices.hpp"
#include "bookServices.hpp"
#include <map>

// =====================================================
// ============== NHÓM: FILE I/O ========================
// =====================================================

// ==========================================
// Function: loadOrdersFromFile
// Mô tả: Đọc dữ liệu đơn hàng từ file CSV
//        - Gom nhiều dòng thành 1 Order (dùng map)
//        - Map bookId → tên sách từ bookService
// Input:
//   - filepath: đường dẫn file
// Output: void
// ==========================================
void OrderService::loadOrdersFromFile(std::string filepath)
{
    std::ifstream file(filepath);
    std::string line;

    orders.clear();
    std::map<std::string, Order> orderMap;

    // Load dữ liệu sách để map tên sách
    bookService bs;
    bs.loadBooksFromFile("data/data.csv");

    // ==========================================
    // Helper: trim khoảng trắng đầu/cuối
    // ==========================================
    auto trim = [](std::string &s)
    {
        if (s.empty())
            return;
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    };

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);

        std::string orderId, customerId;
        std::string bookId, quantityStr, priceStr, totalStr, status;

        // ===== Đọc dữ liệu từ CSV =====
        getline(ss, orderId, ',');
        getline(ss, customerId, ',');
        getline(ss, bookId, ',');
        getline(ss, quantityStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, totalStr, ',');
        getline(ss, status, ',');

        // ===== Chuẩn hóa dữ liệu (trim) =====
        trim(orderId);
        trim(customerId);
        trim(bookId);
        trim(quantityStr);
        trim(priceStr);
        trim(status);

        // ===== Xử lý thiếu dữ liệu =====
        if (orderId.empty())
        {
            orderId = std::to_string(time(nullptr)) + std::to_string(rand() % 1000);
        }

        if (customerId.empty())
        {
            customerId = "Guest";
        }

        // ===== Tạo Order nếu chưa tồn tại =====
        if (orderMap.find(orderId) == orderMap.end())
        {
            Order order(orderId, customerId, {}, status);
            orderMap[orderId] = order;
        }

        // ==========================================
        // Tạo OrderItem
        // ==========================================
        OrderItem item;
        item.bookId = bookId;

        try
        {
            item.quantity = std::stoi(quantityStr);
            item.price = std::stod(priceStr);
        }
        catch (...)
        {
            // Nếu lỗi dữ liệu → bỏ qua dòng
            continue;
        }

        // ===== Map bookId → tên sách =====
        Book *b = bs.getBookById(bookId);
        if (b != nullptr)
            item.name = b->getName();
        else
            item.name = "Unknown";

        // ===== Thêm item vào Order =====
        auto items = orderMap[orderId].getItems();
        items.push_back(item);
        orderMap[orderId].setItems(items);
    }

    // ==========================================
    // Convert map → vector orders
    // ==========================================
    for (auto &pair : orderMap)
    {
        pair.second.calculateTotal();
        orders.push_back(pair.second);
    }
}

// ==========================================
// Function: saveOrdersToFile
// Mô tả: Lưu danh sách đơn hàng ra file CSV
// Lưu ý:
//   - Chỉ lưu item đầu tiên của mỗi order
// Input:
//   - filepath: đường dẫn file
// Output: void
// ==========================================
void OrderService::saveOrdersToFile(std::string filepath)
{
    std::ofstream file(filepath);

    for (auto &o : orders)
    {
        auto items = o.getItems();

        if (!items.empty())
        {
            file << o.getOrderId() << ","
                 << o.getCustomerId() << ","
                 << items[0].bookId << ","
                 << items[0].quantity << ","
                 << items[0].price << ","
                 << o.getTotalAmount() << ","
                 << o.getStatus() << "\n";
        }
    }
}

// =====================================================
// ============== NHÓM: TRUY XUẤT DỮ LIỆU ==============
// =====================================================

// ==========================================
// Function: getAllOrders
// Mô tả: Lấy toàn bộ danh sách đơn hàng
// Input: none
// Output:
//   - vector<Order>: bản sao danh sách đơn hàng
// ==========================================
std::vector<Order> OrderService::getAllOrders() const
{
    return orders;
}

// =====================================================
// ============== NHÓM: CRUD ORDER ======================
// =====================================================

// ==========================================
// Function: addOrder
// Mô tả: Thêm một đơn hàng mới vào hệ thống
// Input:
//   - order: đối tượng Order
// Output: void
// ==========================================
void OrderService::addOrder(const Order &order)
{
    orders.push_back(order);
}

// ==========================================
// Function: updateStatus
// Mô tả: Cập nhật trạng thái đơn hàng
// Input:
//   - orderId: mã đơn hàng
//   - newStatus: trạng thái mới
// Output: void
// ==========================================
void OrderService::updateStatus(std::string orderId, std::string newStatus)
{
    for (auto &o : orders)
    {
        if (o.getOrderId() == orderId)
        {
            o.setStatus(newStatus);
        }
    }
}