#pragma once
#include "order.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

class OrderService
{
private:
    std::vector<Order> orders;

public:
    void loadOrdersFromFile(std::string filepath);
    void saveOrdersToFile(std::string filepath);

    std::vector<Order> getAllOrders() const;

    void addOrder(const Order &order);
    void updateStatus(std::string orderId, std::string newStatus);
};