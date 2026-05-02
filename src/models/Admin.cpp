#include "Admin.hpp"

// ================= CONSTRUCTOR =================
Admin::Admin(const string &Name, const string &gender, int age,
             const string &account, const string &password)
    : User(Name, gender, age),
      account(account),
      password(password)
{
}

// ================= GETTER =================
string Admin::getAccount() const
{
    return account;
}

string Admin::getPassword() const
{
    return password;
}

// ================= SETTER =================
void Admin::setAccount(const string &acc)
{
    account = acc;
}

void Admin::setPassword(const string &pass)
{
    password = pass;
}

// ================= LOGIN =================
bool Admin::login(const string &username, const string &pass) const
{
    return username == account && pass == password;
}

// ================= POLYMORPHISM =================
string Admin::getRole() const
{
    return "Admin";
}