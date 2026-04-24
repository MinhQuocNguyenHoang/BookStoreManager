#pragma once
#include <Customer.hpp>
#include <vector>
#include <string>

class customerService
{
private:
    std::vector<Customer> customers;

public:
    void addCustomer(std::string id, std::string name, std::string gender, std::string phone);
    std::vector<Customer> getAllCustomers() const;

    void loadCustomersFromFile(std::string filepath);
    void saveCustomersToFile(std::string filepath);
};