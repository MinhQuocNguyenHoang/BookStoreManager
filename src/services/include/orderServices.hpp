#pragma once
#include "order.hpp"
#include "IService.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class OrderService : public IService
{
private:
    vector<Order> orders;

public:
    // File (đa hình từ IService)
    void loadFromFile(string filepath) override;
    void saveToFile(string filepath) override;

    // Getter
    vector<Order> getAllOrders() const;

    // CRUD
    void addOrder(const Order &order);
    void updateStatus(const string &orderId, const string &newStatus);
};