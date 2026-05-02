#include "order.hpp"

// ================= CONSTRUCTOR =================
Order::Order()
    : orderId(""),
      customerId(""),
      items(),
      totalAmount(0.0),
      status("Pending")
{
}

Order::Order(const string &oId,
             const string &cId,
             const vector<OrderItem> &items,
             const string &status)
    : orderId(oId),
      customerId(cId),
      items(items),
      totalAmount(0.0),
      status(status)
{
    calculateTotal();
}

// ================= GETTER =================
string Order::getOrderId() const
{
    return orderId;
}

string Order::getCustomerId() const
{
    return customerId;
}

double Order::getTotalAmount() const
{
    return totalAmount;
}

string Order::getStatus() const
{
    return status;
}

const vector<OrderItem> &Order::getItems() const
{
    return items;
}

// ================= SETTER =================
void Order::setStatus(const string &newStatus)
{
    status = newStatus;
}

void Order::setItems(const vector<OrderItem> &newItems)
{
    items = newItems;
    calculateTotal();
}

// ================= BEHAVIOR =================
void Order::addItem(const OrderItem &item)
{
    items.push_back(item);
    calculateTotal();
}

// ================= LOGIC =================
void Order::calculateTotal()
{
    totalAmount = 0.0;
    for (const auto &item : items)
    {
        totalAmount += item.quantity * item.price;
    }
}