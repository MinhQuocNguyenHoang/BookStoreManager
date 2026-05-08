#pragma once
#include <iostream>
#include <string>
#include "webview/webview.h"
#include <windows.h>

#include "Admin.hpp"
#include "bookServices.hpp"
#include "orderServices.hpp"
#include "customerServices.hpp"
#include "IService.hpp"

#include <filesystem>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;
namespace fs = std::filesystem;

class SystemApp
{
private:
    webview::webview w{true, nullptr};

    // ===== SERVICE =====
    bookService bs;
    customerService cs;
    OrderService os;

    // ===== POLYMORPHISM SAFE =====
    map<string, IService *> serviceMap;

    // ===== ADMIN =====
    Admin admin{"Quoc", "Male", 18};

public:
    void init();
    void run();
};