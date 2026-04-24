#pragma once
#include <iostream>
#include <string>
#include <vector>

struct OrderItem
{
    std::string bookId;
    std::string name;
    int quantity;
    double price;
    double getTotal() const
    {
        return quantity * price;
    }
};

class Order
{
private:
    std::string orderId;
    std::string customerId;
    std::vector<OrderItem> items;
    double totalAmount;
    std::string status;

public:
    Order();
    Order(std::string oId,
          std::string cId,
          std::vector<OrderItem> items,
          std::string status);

    // Getters
    std::string getOrderId() const;
    std::string getCustomerId() const;
    double getTotalAmount() const;
    std::string getStatus() const;
    std::vector<OrderItem> &getItems();

    // Setters (Dùng để Service cập nhật dữ liệu)
    void setStatus(std::string newStatus);
    void setTotalAmount(double amount);
    void setItems(const std::vector<OrderItem> &newItems);
    void calculateTotal();
};