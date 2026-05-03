#include "orderServices.hpp"
#include "bookServices.hpp"
#include <map>
#include <ctime>

// =====================================================
// ================= FILE I/O ===========================
// =====================================================

void OrderService::loadFromFile(string filepath)
{
    ifstream file(filepath);
    string line;

    orders.clear();
    map<string, Order> orderMap;

    // Load books để map tên
    bookService bs;
    bs.loadFromFile("data/data.csv");

    auto trim = [](string &s)
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

        stringstream ss(line);

        string orderId, customerId;
        string bookId, quantityStr, priceStr, totalStr, status;

        getline(ss, orderId, ',');
        getline(ss, customerId, ',');
        getline(ss, bookId, ',');
        getline(ss, quantityStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, totalStr, ',');
        getline(ss, status, ',');

        trim(orderId);
        trim(customerId);
        trim(bookId);
        trim(quantityStr);
        trim(priceStr);
        trim(status);

        if (orderId.empty())
            orderId = to_string(time(nullptr));

        if (customerId.empty())
            customerId = "Guest";

        // tạo order nếu chưa có
        if (orderMap.find(orderId) == orderMap.end())
        {
            orderMap[orderId] = Order(orderId, customerId, {}, status);
        }

        OrderItem item;
        item.bookId = bookId;

        try
        {
            item.quantity = stoi(quantityStr);
            item.price = stod(priceStr);
        }
        catch (...)
        {
            continue;
        }

        // map tên sách
        Book *b = bs.getBookById(bookId);
        item.name = (b != nullptr) ? b->getName() : "Unknown";

        orderMap[orderId].addItem(item);
    }

    // convert map -> vector
    for (auto &p : orderMap)
    {
        p.second.calculateTotal();
        orders.push_back(p.second);
    }
}

void OrderService::saveToFile(string filepath)
{
    ofstream file(filepath);

    for (auto &o : orders)
    {
        const auto &items = o.getItems();

        for (auto &item : items) // LOOP TẤT CẢ ITEM
        {
            file << o.getOrderId() << ","
                 << o.getCustomerId() << ","
                 << item.bookId << ","
                 << item.quantity << ","
                 << item.price << ","
                 << o.getTotalAmount() << ","
                 << o.getStatus() << "\n";
        }
    }
}

// =====================================================
// ================= GET DATA ===========================
// =====================================================

vector<Order> OrderService::getAllOrders() const
{
    return orders;
}

// =====================================================
// ================= CRUD ===============================
// =====================================================

void OrderService::addOrder(const Order &order)
{
    orders.push_back(order);
}

void OrderService::updateStatus(const string &orderId, const string &newStatus)
{
    for (auto &o : orders)
    {
        if (o.getOrderId() == orderId)
        {
            o.setStatus(newStatus);
        }
    }
}