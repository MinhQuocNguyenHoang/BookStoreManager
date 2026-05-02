#include "customerServices.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// =====================================================
// ================= CRUD CUSTOMER ======================
// =====================================================

void customerService::addCustomer(const string &id,
                                  const string &name,
                                  const string &gender,
                                  const string &phone)
{
    customers.emplace_back(id, name, gender, phone);
}

// =====================================================
// ================= GET DATA ===========================
// =====================================================

vector<Customer> customerService::getAllCustomers() const
{
    return customers;
}

// =====================================================
// ================= FILE I/O ===========================
// =====================================================

void customerService::loadFromFile(string filepath)
{
    ifstream file(filepath);

    if (!file.is_open())
    {
        return;
    }

    customers.clear();

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        string id, name, gender, phone;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, gender, ',');
        getline(ss, phone, ',');

        customers.emplace_back(id, name, gender, phone);
    }

    file.close();
}

void customerService::saveToFile(string filepath)
{
    ofstream file(filepath);

    for (const auto &c : customers)
    {
        file << c.getId() << ","
             << c.getName() << ","
             << c.getGender() << ","
             << c.getPhone() << "\n";
    }

    file.close();
}