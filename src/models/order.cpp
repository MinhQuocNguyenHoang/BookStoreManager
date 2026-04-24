#include <order.hpp>

Order::Order()
{
    orderId = "";
    customerId = "";
    totalAmount = 0.0;
    status = "Chưa xử lý";
}

Order::Order(std::string oId,
             std::string cId,
             std::vector<OrderItem> items,
             std::string status)
{
    this->orderId = oId;
    this->customerId = cId;
    this->items = items;
    this->status = status;

    calculateTotal();
}

std::string Order::getOrderId() const
{
    return orderId;
}

std::string Order::getCustomerId() const
{
    return customerId;
}

double Order::getTotalAmount() const
{
    return totalAmount;
}

std::string Order::getStatus() const
{
    return status;
}

std::vector<OrderItem> &Order::getItems()
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

void Order::calculateTotal()
{
    double sum = 0;

    for (auto &item : items)
    {
        sum += item.quantity * item.price;
    }

    totalAmount = sum;
}