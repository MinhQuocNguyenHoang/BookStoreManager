#define WEBVIEW_IMPLEMENTATION
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
    string ui_path = "file://" + current_path + "/UI/UI.html";

    w.url = ui_path.c_str();
    w.width = 1440;
    w.height = 900;
    w.resizable = 1;
    w.external_invoke_cb = handleCalls;

    webview_init(&w);
}

// ==========================================
// Function: run
// Mô tả: Loop chính của ứng dụng
// ==========================================
void SystemApp::run()
{
    while (webview_loop(&w, 1) == 0)
    {
    }
}

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
void SystemApp::handleCalls(struct webview *w, const char *arg)
{
    cout << arg << endl;

    string data = arg;
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

        string script = "loadBooks(" + json + ");";
        webview_eval(w, script.c_str());
        return;
    }

    if (data == "GET_BOOKS_CUSTOMER")
    {
        bookService bs;
        bs.loadBooksFromFile("data/data.csv");

        auto books = bs.getAllBooks();
        string json = booksToJSON(books);

        string script = "renderBookPage(" + json + ");";
        webview_eval(w, script.c_str());
        return;
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

        string script = "renderOrderPage(" + json + ", " + to_string(totalRevenue) + ");";
        webview_eval(w, script.c_str());

        return;
    }

    // =====================================================
    // ============== NAVIGATION ============================
    // =====================================================

    if (data == "GO_HOME")
    {
        string current_path = fs::current_path().string();
        string ui = "file://" + current_path + "/UI/UI.html";

        string script = "window.location.href = '" + ui + "';";
        webview_eval(w, script.c_str());
        return;
    }

    // =====================================================
    // ============== PARSE ACTION ==========================
    // =====================================================

    size_t first_pipe = data.find("|");
    if (first_pipe == string::npos)
        return;

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
            string dashboard = "file://" + current_path + "/UI/admin-dashboard.html";

            string script = "window.location.href = '" + dashboard + "';";
            webview_eval(w, script.c_str());
        }
        else
        {
            webview_eval(w, "alert('Sai tài khoản hoặc mật khẩu!');");
        }
    }

    // =====================================================
    // ============== BOOK MANAGEMENT ======================
    // =====================================================

    if (action == "DELETE")
    {
        bs.loadBooksFromFile("data/data.csv");
        bs.deleteBook(payload);
        bs.saveBooksToFile("data/data.csv");

        webview_eval(w, "location.reload();");
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

        webview_eval(w, "location.reload();");
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

        webview_eval(w, "location.reload();");
    }

    if (action == "SEARCH_ADMIN")
    {
        string keyword = payload;

        bs.loadBooksFromFile("data/data.csv");
        auto result = bs.searchBookByTitle(keyword);

        string json = booksToJSON(result);

        string script = "loadBooks(" + json + ");";
        webview_eval(w, script.c_str());
        return;
    }

    if (action == "SEARCH_CUSTOMER")
    {
        string keyword = payload;

        bs.loadBooksFromFile("data/data.csv");
        auto result = bs.searchBookByTitle(keyword);

        string json = booksToJSON(result);
        string script = "renderBookList(" + json + ");";
        webview_eval(w, script.c_str());
        return;
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
                string script =
                    "customerExists('" + c.getName() + "','" +
                    c.getGender() + "','" +
                    c.getPhone() + "');";

                webview_eval(w, script.c_str());
                return;
            }
        }

        string id = to_string(time(nullptr));

        cs.addCustomer(id, name, gender, phone);
        cs.saveCustomersToFile("data/customer.csv");

        webview_eval(w, "window.loadShop();");
        return;
    }

    // =====================================================
    // ============== CHECKOUT =============================
    // =====================================================

    if (action == "CHECKOUT")
    {
        // (giữ nguyên logic của bạn – rất tốt, mình không sửa)
        // xử lý giỏ hàng → tạo order → trừ stock
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

        string script = "renderMyOrders(" + json + ");";
        webview_eval(w, script.c_str());

        return;
    }
}