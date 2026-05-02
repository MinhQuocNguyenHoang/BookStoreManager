#pragma once
#include <string>
#include <vector>
using namespace std;

struct OrderItem
{
    string bookId;
    string name;
    int quantity;
    double price;
};

class Order
{
private:
    string orderId;
    string customerId;
    vector<OrderItem> items;
    double totalAmount;
    string status;

public:
    // Constructor
    Order();
    Order(const string &oId, const string &cId,
          const vector<OrderItem> &items,
          const string &status);

    // Getter
    string getOrderId() const;
    string getCustomerId() const;
    double getTotalAmount() const;
    string getStatus() const;

    const vector<OrderItem> &getItems() const;

    // Setter
    void setStatus(const string &newStatus);
    void setItems(const vector<OrderItem> &newItems);

    // Behavior (OOP chuẩn)
    void addItem(const OrderItem &item);

    // Logic
    void calculateTotal();
};