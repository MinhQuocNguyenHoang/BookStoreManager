# BookStoreManager

BookStoreManager is a bookstore management application developed using C++. The system provides functionalities for managing books, customers, and orders. It integrates a web-based user interface using WebView.

## Introduction

This project simulates a basic bookstore management system. It allows users to store, manage, and process data related to books, customers, and orders. The system is designed with a clear separation between data models, business logic, and user interface to improve maintainability.

## Features

### Book Management

* Add new books
* Update book information
* Delete books
* Search books by name

### Customer Management

* Add new customers
* Update customer information
* View customer details

### Order Management

* Create new orders
* Update order status
* View order history

### User Interface

* Built using HTML, CSS, and JavaScript
* Integrated with C++ using WebView2
* Provides interactive user experience

## Project Structure

```
BookStoreManager/
│
├── src/
│   ├── models/        // Data models (Book, Customer, Order, User)
│   ├── services/      // Business logic
│   ├── webview/       // WebView integration
│   └── main.cpp       // Entry point
│
├── data/              // CSV data storage
│   ├── books.csv
│   ├── customers.csv
│   └── orders.csv
│
├── ui/                // Frontend (HTML/CSS/JS)
│
└── script_run.sh      // Build and run script
```

## Technologies Used

* C++
* STL (Standard Template Library)
* File handling with CSV
* HTML, CSS, JavaScript
* WebView2
* MSYS2 (for build and execution on Windows)

## How to Run

### Using MSYS2 (Windows)

1. Open MSYS2 Mingw64 terminal

2. Navigate to the project directory:

Example:

```
cd /c/path/to/BookStoreManager
```

3. Run the script:

```
./script_run.sh
```

## Design Overview

The system follows a layered structure:

* Models: represent data entities such as Book, Customer, and Order
* Services: handle business logic and data processing
* WebView/UI: provide user interaction through a web interface

This structure improves code organization and scalability.

## Future Improvements

* Replace CSV with a database system
* Improve performance for large datasets
* Add authentication and user roles
* Enhance UI design and usability

## Author

Nguyen Hoang Minh Quoc \\
Pham Quoc Trung \\
Pham Mai Dieu Thao \\
Pham Thai Cam Nhung \\
