#pragma once
#include <iostream>
#include <string>

// #ifdef WEBVIEW_GTK
// #include <gtk/gtk.h>
// #include <webkit2/webkit2.h>
// #endif
// #include "webview.h"
#include "webview/webview.h"
#include <windows.h>

#include <Admin.hpp>
#include <bookServices.hpp>
#include <orderServices.hpp>
#include <customerServices.hpp>
#include <filesystem>
#include <unistd.h>
#include <sstream>
#include <iomanip>
using namespace std;
namespace fs = std::filesystem;

class SystemApp
{
private:
    webview::webview w{true, nullptr};

public:
    void init();
    void run();
};