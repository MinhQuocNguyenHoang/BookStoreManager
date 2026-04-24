#pragma once
#include <iostream>
#include <string>

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#define WEBVIEW_GTK
#include "webview.h"

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
    struct webview w;

public:
    void init();
    void run();
    static void handleCalls(struct webview *w, const char *arg);
};