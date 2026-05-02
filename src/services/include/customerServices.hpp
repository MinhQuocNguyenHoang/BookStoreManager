#pragma once
#include "Customer.hpp"
#include "IService.hpp"
#include <vector>
#include <string>
using namespace std;

class customerService : public IService
{
private:
    vector<Customer> customers;

public:
    // CRUD
    void addCustomer(const string &id,
                     const string &name,
                     const string &gender,
                     const string &phone);

    vector<Customer> getAllCustomers() const;

    // File (đa hình từ IService)
    void loadFromFile(string filepath) override;
    void saveToFile(string filepath) override;
};