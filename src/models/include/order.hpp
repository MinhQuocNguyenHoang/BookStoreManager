#pragma once
#include <iostream>
#include <string>
#include <vector>

struct OrderItem
{
    std::string bookId;
    int quantity;
    double price;
};

class Order
{
private:
    std::string orderId;
    std::string customerId;
    std::string orderDate;
    std::vector<OrderItem> items;
    double totalAmount;
    std::string status;

public:
    Order();
    Order(std::string oId, std::string cId, std::string date);

    // Getters
    std::string getOrderId() const;
    std::string getCustomerId() const;
    std::string getOrderDate() const;
    double getTotalAmount() const;
    std::string getStatus() const;
    std::vector<OrderItem> getItems() const;

    // Setters (Dùng để Service cập nhật dữ liệu)
    void setStatus(std::string newStatus);
    void setTotalAmount(double amount);
    void setItems(const std::vector<OrderItem> &newItems);
};