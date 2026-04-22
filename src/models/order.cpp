#include <order.hpp>

Order::Order()
{
    orderId = "";
    customerId = "";
    orderDate = "";
    totalAmount = 0.0;
    status = "Chưa xử lý"; // Trạng thái mặc định khi mới tạo đơn
}

Order::Order(std::string oId, std::string cId, std::string date)
{
    orderId = oId;
    customerId = cId;
    orderDate = date;
    totalAmount = 0.0;     // Đơn mới chưa có sách nên tổng tiền bằng 0
    status = "Chưa xử lý"; // Trạng thái mặc định
}

std::string Order::getOrderId() const
{
    return orderId;
}

std::string Order::getCustomerId() const
{
    return customerId;
}

std::string Order::getOrderDate() const
{
    return orderDate;
}

double Order::getTotalAmount() const
{
    return totalAmount;
}

std::string Order::getStatus() const
{
    return status;
}

std::vector<OrderItem> Order::getItems() const
{
    return items;
}

void Order::setStatus(std::string newStatus)
{
    status = newStatus;
}

void Order::setTotalAmount(double amount)
{
    totalAmount = amount;
}

void Order::setItems(const std::vector<OrderItem> &newItems)
{
    items = newItems;
}