#include "System.hpp"
#include <cstdlib>
#include <ctime>

// ================= HELPER POLYMORPHISM =================
void load(map<string, IService *> &m, const string &key, const string &file)
{
    m[key]->loadFromFile(file);
}

void save(map<string, IService *> &m, const string &key, const string &file)
{
    m[key]->saveToFile(file);
}

// ================= JSON =================
string generateId()
{
    return to_string(rand() % 10000);
}

static string booksToJSON(vector<Book> books)
{
    string json = "[";
    for (auto &b : books)
    {
        json += "{";
        json += "\"id\":\"" + b.getId() + "\",";
        json += "\"name\":\"" + b.getName() + "\",";
        json += "\"type\":\"" + b.getType() + "\",";
        json += "\"price\":" + to_string((int)b.getPrice()) + ",";
        json += "\"stock\":" + to_string(b.getStock());
        json += "},";
    }
    if (json.back() == ',')
        json.pop_back();
    json += "]";
    return json;
}

static string ordersToJSON(vector<Order> orders)
{
    string json = "[";
    for (auto &o : orders)
    {
        string names = "";
        int totalQuantity = 0;

        for (auto &item : o.getItems())
        {
            names += item.name + " x" + to_string(item.quantity) + "\\n";
            totalQuantity += item.quantity;
        }

        json += "{";
        json += "\"id\":\"" + o.getOrderId() + "\",";
        json += "\"customerId\":\"" + o.getCustomerId() + "\",";
        json += "\"name\":\"" + names + "\",";
        json += "\"quantity\":" + to_string(totalQuantity) + ",";
        json += "\"total\":" + to_string((long long)o.getTotalAmount()) + ",";
        json += "\"status\":\"" + o.getStatus() + "\"";
        json += "},";
    }
    if (json.back() == ',')
        json.pop_back();
    json += "]";
    return json;
}

// ================= INIT =================
void SystemApp::init()
{
    string ui = "file:///" + fs::current_path().string() + "/UI/UI.html";

    w.set_title("NhaSachFetel");
    w.set_size(1440, 900, WEBVIEW_HINT_NONE);
    w.navigate(ui);

    // ===== POLYMORPHISM =====
    serviceMap["book"] = &bs;
    serviceMap["customer"] = &cs;
    serviceMap["order"] = &os;

    w.bind("callCpp", [this](const string &arg) -> string
           {
        string data = arg;

        if (data.front() == '[') data = data.substr(1);
        if (data.back() == ']') data.pop_back();
        if (data.front() == '"') data = data.substr(1);
        if (data.back() == '"') data.pop_back();

        size_t pos = data.find("|");
        string action = (pos == string::npos) ? data : data.substr(0, pos);
        string payload = (pos == string::npos) ? "" : data.substr(pos + 1);

        // ===== GO HOME =====
        if (action == "GO_HOME")
        {
            string path = "file:///" + fs::current_path().string() + "/UI/UI.html";
            w.navigate(path);
            return "";
        }

        // ===== LOAD BOOK =====
        if (action == "GET_BOOKS")
        {
            load(serviceMap, "book", "data/data.csv");
            w.eval("loadBooks(" + booksToJSON(bs.getAllBooks()) + ");");
        }

        if (action == "GET_BOOKS_CUSTOMER")
        {
            load(serviceMap, "book", "data/data.csv");
            w.eval("renderBookPage(" + booksToJSON(bs.getAllBooks()) + ");");
        }

        if (action == "GET_ORDERS")
        {
            load(serviceMap, "order", "data/orders.csv");

            double revenue = 0;
            for (auto &o : os.getAllOrders())
                if (o.getStatus() == "Done")
                    revenue += o.getTotalAmount();

            w.eval("renderOrderPage(" +
                ordersToJSON(os.getAllOrders()) + "," +
                to_string(revenue) + ");");
        }

        // ===== LOGIN =====
        if (action == "LOGIN")
        {
            size_t p = payload.find("|");
            string acc = payload.substr(0, p);
            string pass = payload.substr(p + 1);

            if (admin.login(acc, pass))
            {
                string path = "file:///" + fs::current_path().string() + "/UI/admin-dashboard.html";
                w.navigate(path);
            }
            else
                w.eval("alert('Sai tài khoản hoặc mật khẩu!');");
        }

        // ===== SEARCH =====
        if (action == "SEARCH_ADMIN")
        {
            load(serviceMap, "book", "data/data.csv");
            w.eval("loadBooks(" + booksToJSON(bs.searchBookByTitle(payload)) + ");");
        }

        if (action == "SEARCH_CUSTOMER")
        {
            load(serviceMap, "book", "data/data.csv");
            w.eval("renderBookList(" + booksToJSON(bs.searchBookByTitle(payload)) + ");");
        }

        // ===== CRUD =====
        if (action == "ADD")
        {
            stringstream ss(payload);
            string name, type, price, stock;

            getline(ss, name, '|');
            getline(ss, type, '|');
            getline(ss, price, '|');
            getline(ss, stock, '|');

            load(serviceMap, "book", "data/data.csv");
            string id = generateId();

            bs.addBook(id,
                       name, type, stof(price), stoi(stock));

            save(serviceMap, "book", "data/data.csv");

            w.eval("location.reload();");
        }

        if (action == "DELETE")
        {
            load(serviceMap, "book", "data/data.csv");

            bs.deleteBook(payload);

            save(serviceMap, "book", "data/data.csv");

            w.eval("location.reload();");
        }

        if (action == "UPDATE")
        {
            stringstream ss(payload);
            string id, amount;

            getline(ss, id, '|');
            getline(ss, amount, '|');

            load(serviceMap, "book", "data/data.csv");

            bs.updateStock(id, stoi(amount));

            save(serviceMap, "book", "data/data.csv");

            w.eval("location.reload();");
        }

        // ===== CUSTOMER =====
        if (action == "ADD_CUSTOMER")
        {
            stringstream ss(payload);
            string name, gender, phone;

            getline(ss, name, '|');
            getline(ss, gender, '|');
            getline(ss, phone, '|');

            load(serviceMap, "customer", "data/customer.csv");
            bool exists = false;
            for (auto &c : cs.getAllCustomers())  // giả sử có hàm này
            {
                if (c.getPhone() == phone)
                {
                    exists = true;
                    break;
                }
            }

            if(!exists){
            cs.addCustomer(to_string(time(nullptr)), name, gender, phone);

            save(serviceMap, "customer", "data/customer.csv");
            }

            w.eval("window.loadShop();");
        }

        // ===== CHECKOUT =====
        if (action == "CHECKOUT")
        {
            stringstream ss(payload);
            string customer, items;

            getline(ss, customer, '|');
            getline(ss, items);
            cout << "ITEMS STRING: " << items << endl;
            load(serviceMap, "book", "data/data.csv");
            load(serviceMap, "order", "data/orders.csv");

            vector<OrderItem> orderItems;

            stringstream itemStream(items);
            string item;

            while (getline(itemStream, item, '|'))
            {
                size_t p = item.find(":");
                string id = item.substr(0, p);
                int qty = stoi(item.substr(p + 1));

                for (auto &b : bs.getAllBooks())
                {
                    if (b.getId() == id)
                    {
                        b.setStock(b.getStock() - qty);
                        orderItems.push_back({id, b.getName(), qty, b.getPrice()});
                    }
                }
            }

            Order order(to_string(time(nullptr)), customer, orderItems, "Done");

            os.addOrder(order);

            save(serviceMap, "order", "data/orders.csv");
            save(serviceMap, "book", "data/data.csv");
        }

        // ===== MY ORDERS =====
        if (action == "GET_MY_ORDERS")
        {
            load(serviceMap, "order", "data/orders.csv");

            vector<Order> myOrders;
            for (auto &o : os.getAllOrders())
                if (o.getCustomerId() == payload)
                    myOrders.push_back(o);

            w.eval("renderMyOrders(" + ordersToJSON(myOrders) + ");");
        }

        return ""; });
}

void SystemApp::run()
{
    w.run();
}