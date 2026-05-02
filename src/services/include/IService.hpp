#pragma once
#include <string>
using namespace std;

class IService
{
public:
    // 🔥 đa hình (pure virtual)
    virtual void loadFromFile(string filepath) = 0;
    virtual void saveToFile(string filepath) = 0;

    // destructor ảo (chuẩn OOP)
    virtual ~IService() {}
};