// #define WEBVIEW_IMPLEMENTATION
// #include <System.hpp>
// #include <windows.h>
#include <System.hpp>

// =====================================================
// ============== HELPER: CONVERT JSON ==================
// =====================================================

// ==========================================
// Function: booksToJSON
// Mô tả: Convert danh sách Book → JSON string
// Dùng để gửi dữ liệu từ C++ sang JS
// ==========================================
static string booksToJSON(vector<Book> books)
{
    string json = "[";

    for (size_t i = 0; i < books.size(); i++)
    {
        json += "{";
        json += "\"id\":\"" + books[i].getId() + "\",";
        json += "\"name\":\"" + books[i].getName() + "\",";
        json += "\"type\":\"" + books[i].getType() + "\",";
        ostringstream oss;
        oss << fixed << setprecision(2) << books[i].getPrice();
        json += "\"price\":" + oss.str() + ",";
        json += "\"stock\":" + to_string(books[i].getStock());
        json += "}";

        if (i != books.size() - 1)
            json += ",";
    }

    json += "]";
    return json;
}

// ==========================================
// Function: ordersToJSON
// Mô tả: Convert danh sách Order → JSON
// - Gom nhiều item thành 1 chuỗi name
// - Tính tổng quantity
// ==========================================
string ordersToJSON(vector<Order> orders)
{
    string json = "[";

    for (size_t i = 0; i < orders.size(); i++)
    {
        auto items = orders[i].getItems();

        string names = "";
        int totalQuantity = 0;

        for (auto &item : items)
        {
            names += item.name + " x" + to_string(item.quantity) + "\\n";
            totalQuantity += item.quantity;
        }

        if (!names.empty())
        {
            names.pop_back();
            names.pop_back();
        }

        json += "{";
        json += "\"id\":\"" + orders[i].getOrderId() + "\",";
        json += "\"customerId\":\"" + orders[i].getCustomerId() + "\",";
        json += "\"name\":\"" + names + "\",";
        json += "\"quantity\":" + to_string(totalQuantity) + ",";
        json += "\"total\":" + to_string((long long)orders[i].getTotalAmount()) + ",";
        json += "\"status\":\"" + orders[i].getStatus() + "\"";
        json += "}";

        if (i != orders.size() - 1)
            json += ",";
    }

    json += "]";
    return json;
}

// =====================================================
// ================= SYSTEM CORE ========================
// =====================================================

static Admin admin("Quoc", "Male", 18);

// ==========================================
// Function: init
// Mô tả: Khởi tạo webview + load UI.html
// ==========================================
void SystemApp::init()
{
    string current_path = fs::current_path().string();
    string ui = "file://" + current_path + "/UI/UI.html";
    w.set_title("NhaSachFetel");
    w.set_size(1440, 900, WEBVIEW_HINT_NONE);

    w.navigate(ui);

    // =====================================================
    // ================= HANDLE EVENT =======================
    // =====================================================

    // ==========================================
    // Function: handleCalls
    // Mô tả:
    // - Nhận request từ JS (string arg)
    // - Parse action
    // - Gọi service tương ứng
    // - Trả dữ liệu lại bằng JS (webview_eval)
    // ==========================================
    w.bind("callCpp", [&](const string &arg) -> string
           {
        string data = arg;

    // remove JSON wrapper ["..."]
    if (!data.empty() && data.front() == '[')
        data = data.substr(1);

    if (!data.empty() && data.back() == ']')
        data.pop_back();

    if (!data.empty() && data.front() == '"')
        data = data.substr(1);

    if (!data.empty() && data.back() == '"')
        data.pop_back();
    cout << data << endl;

    bookService bs;

    // =====================================================
    // ============== LOAD DATA =============================
    // =====================================================

    if (data == "GET_BOOKS")
    {
        bookService bs;
        bs.loadBooksFromFile("data/data.csv");

        auto books = bs.getAllBooks();
        string json = booksToJSON(books);

        // string script = "loadBooks(" + json + ");";
        // webview_eval(w, script.c_str());
        w.eval("loadBooks(" + json + ");");
        return "";
    }

    if (data == "GET_BOOKS_CUSTOMER")
    {
        bookService bs;
        bs.loadBooksFromFile("data/data.csv");

        auto books = bs.getAllBooks();
        string json = booksToJSON(books);

        // string script = "renderBookPage(" + json + ");";
        // webview_eval(w, script.c_str());
        w.eval("renderBookPage(" + json + ");");
        return "";
    }

    if (data == "GET_ORDERS")
    {
        OrderService os;
        os.loadOrdersFromFile("data/orders.csv");

        auto orders = os.getAllOrders();
        double totalRevenue = 0;

        for (auto &order : orders)
        {
            if (order.getStatus() == "Done")
            {
                totalRevenue += order.getTotalAmount();
            }
        }

        string json = ordersToJSON(orders);

        // string script = "renderOrderPage(" + json + ", " + to_string(totalRevenue) + ");";
        // webview_eval(w, script.c_str());
        w.eval("renderOrderPage(" + json + "," + to_string(totalRevenue) + ");");

        return "";
    }

    // =====================================================
    // ============== NAVIGATION ============================
    // =====================================================

    if (data == "GO_HOME")
    {
        string current_path = fs::current_path().string();
        string ui = "file:///" + current_path + "/UI/UI.html";

        // string script = "window.location.href = '" + ui + "';";
        // webview_eval(w, script.c_str());
        // w.eval("window.location.href='" + ui + "';");
        w.navigate(ui);
        return "";
    }

    // =====================================================
    // ============== PARSE ACTION ==========================
    // =====================================================

    size_t first_pipe = data.find("|");
    if (first_pipe == string::npos)
        return "";

    string action = data.substr(0, first_pipe);
    string payload = data.substr(first_pipe + 1);

    // =====================================================
    // ============== AUTH ================================
    // =====================================================

    if (action == "LOGIN")
    {
        size_t second_pipe = payload.find("|");

        string account = payload.substr(0, second_pipe);
        string pass = payload.substr(second_pipe + 1);

        if (admin.login(account, pass))
        {
            string current_path = fs::current_path().string();
            string dashboard = "file:///" + current_path + "/UI/admin-dashboard.html";
            cout<<dashboard<<endl;
            // string script = "window.location.href = '" + dashboard + "';";
            // webview_eval(w, script.c_str());
            // w.eval("window.location.href='" + dashboard + "';");
            w.navigate(dashboard);
        }   
        else
        {
            // webview_eval(w, "alert('Sai tài khoản hoặc mật khẩu!');");
             w.eval("alert('Sai tài khoản hoặc mật khẩu!');");
        }
        return "";
    }

    // =====================================================
    // ============== BOOK MANAGEMENT ======================
    // =====================================================

    if (action == "DELETE")
    {
        bs.loadBooksFromFile("data/data.csv");
        bs.deleteBook(payload);
        bs.saveBooksToFile("data/data.csv");

        // webview_eval(w, "location.reload();");
         w.eval("location.reload();");
         return "";
    }

    if (action == "ADD")
    {
        stringstream ss(payload);
        string name, type, priceStr, stockStr;

        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, priceStr, '|');
        getline(ss, stockStr, '|');

        bs.loadBooksFromFile("data/data.csv");

        string id = to_string(bs.getAllBooks().size() + 1);

        bs.addBook(id, name, type, stof(priceStr), stoi(stockStr));
        bs.saveBooksToFile("data/data.csv");

        // webview_eval(w, "location.reload();");
          w.eval("location.reload();");
          return "";
    }

    if (action == "UPDATE")
    {
        stringstream ss(payload);
        string id, amountStr;

        getline(ss, id, '|');
        getline(ss, amountStr, '|');

        bs.loadBooksFromFile("data/data.csv");

        bs.updateStock(id, stoi(amountStr));
        bs.saveBooksToFile("data/data.csv");

        // webview_eval(w, "location.reload();");
          w.eval("location.reload();");
        return "";
    }

    if (action == "SEARCH_ADMIN")
    {
        string keyword = payload;

        bs.loadBooksFromFile("data/data.csv");
        auto result = bs.searchBookByTitle(keyword);

        string json = booksToJSON(result);

        // string script = "loadBooks(" + json + ");";
        // webview_eval(w, script.c_str());
        w.eval("loadBooks(" + json + ");");
        return "";
    }

    if (action == "SEARCH_CUSTOMER")
    {
        string keyword = payload;

        bs.loadBooksFromFile("data/data.csv");
        auto result = bs.searchBookByTitle(keyword);

        string json = booksToJSON(result);
        // string script = "renderBookList(" + json + ");";
        // webview_eval(w, script.c_str());
         w.eval("renderBookList(" + json + ");");
        return "";
    }

    // =====================================================
    // ============== CUSTOMER =============================
    // =====================================================

    if (action == "ADD_CUSTOMER")
    {
        stringstream ss(payload);
        string name, gender, phone;

        getline(ss, name, '|');
        getline(ss, gender, '|');
        getline(ss, phone, '|');

        customerService cs;
        cs.loadCustomersFromFile("data/customer.csv");

        for (auto &c : cs.getAllCustomers())
        {
            if (c.getPhone() == phone)
            {
                // string script =
                //     "customerExists('" + c.getName() + "','" +
                //     c.getGender() + "','" +
                //     c.getPhone() + "');";

                // webview_eval(w, script.c_str());
                w.eval("customerExists('" + c.getName() + "','" +
                       c.getGender() + "','" + c.getPhone() + "')");
                return "";
            }
        }

        string id = to_string(time(nullptr));

        cs.addCustomer(id, name, gender, phone);
        cs.saveCustomersToFile("data/customer.csv");

        // webview_eval(w, "window.loadShop();");
        w.eval("window.loadShop();");
        return "";
    }

    // =====================================================
    // ============== CHECKOUT =============================
    // =====================================================

    if (action == "CHECKOUT")
    {
        stringstream ss(payload);
        string customerName, itemsStr;

        getline(ss, customerName, '|');
        getline(ss, itemsStr, '|');

        // ===== load book =====
        bookService bs;
        bs.loadBooksFromFile("data/data.csv");

        // ===== load order =====
        OrderService os;
        os.loadOrdersFromFile("data/orders.csv");

        vector<OrderItem> orderItems;

        stringstream itemStream(itemsStr);
        string item;

        bool error = false;

        while (getline(itemStream, item, '|'))
        {
            size_t pos = item.find(":");
            string bookId = item.substr(0, pos);
            int qty = stoi(item.substr(pos + 1));

            // tìm sách
            auto &books = bs.getAllBooks();
            bool found = false;

            for (auto &b : books)
            {
                if (b.getId() == bookId)
                {
                    found = true;

                    // không đủ hàng
                    if (b.getStock() < qty)
                    {
                        // webview_eval(w, "alert('Sách không đủ hàng!');");
                        w.eval("alert('Sách không đủ hàng!');");
                        return "";
                    }

                    // trừ stock
                    b.setStock(b.getStock() - qty);

                    OrderItem oi;
                    oi.bookId = bookId;
                    oi.name = b.getName();
                    oi.price = b.getPrice();
                    oi.quantity = qty;

                    orderItems.push_back(oi);
                }
            }

            if (!found)
            {
                error = true;
                break;
            }
        }

        if (error)
        {
            // webview_eval(w, "alert('Lỗi dữ liệu đơn hàng!');");
            w.eval("alert('Lỗi dữ liệu đơn hàng!');");
            return "";
        }

        // ===== tạo order =====
        string orderId = to_string(time(nullptr));

        Order order(orderId, customerName, orderItems, "Done");

        os.addOrder(order);
        os.saveOrdersToFile("data/orders.csv");

        // ===== lưu lại books =====
        bs.saveBooksToFile("data/data.csv");

        cout << "=> Checkout success\n";

        return "";
    }

    // =====================================================
    // ============== CUSTOMER ORDERS ======================
    // =====================================================

    if (action == "GET_MY_ORDERS")
    {
        string customerName = payload;

        OrderService os;
        os.loadOrdersFromFile("data/orders.csv");

        auto orders = os.getAllOrders();

        vector<Order> myOrders;

        for (auto &o : orders)
        {
            if (o.getCustomerId() == customerName)
            {
                myOrders.push_back(o);
            }
        }

        string json = ordersToJSON(myOrders);

        // string script = "renderMyOrders(" + json + ");";
        // webview_eval(w, script.c_str());
        w.eval("renderMyOrders(" + json + ");");

        return "";
    } 
    return ""; });
}

// ==========================================
// Function: run
// Mô tả: Loop chính của ứng dụng
// ==========================================
void SystemApp::run()
{
    w.run();
}
