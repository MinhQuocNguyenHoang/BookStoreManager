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

### Windows (Pre-built Executable)

The project has already been built into an executable file, so no compilation is required.

#### Steps:

1. Navigate to the project directory:

```
BookStoreManager/
```

2. Locate the executable file:

```
BookStoreManager.exe
```

3. Run the application by one of the following methods:

- Double-click the `.exe` file  
- Or run via terminal:

```
./BookStoreManager.exe
```

---

### Notes

- Make sure all required folders such as `data/` and `ui/` are in the correct relative paths.
- Do not move the `.exe` file outside the project structure unless you update file paths in the code.

### Requirements (for building from source)

To build the project using the provided Makefile on Windows, you need to install MSYS2 and required development tools.

#### 1. Install MSYS2

Download and install from:
https://www.msys2.org/

After installation, open **MSYS2 MSYS terminal** and update the system:

```
pacman -Syu
```

Close the terminal when asked, then open it again and run:

```
pacman -Su
```

---

#### 2. Install MinGW64 Toolchain

Open **MSYS2 MinGW64 terminal** (important) and install required packages:

```
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

(Optional but recommended):

```
pacman -S mingw-w64-x86_64-gdb
```

---

#### 3. Add MinGW64 to PATH (optional)

Add this path to your Windows Environment Variables if needed:

```
C:\msys64\mingw64\bin
```

---

#### 4. WebView2 Runtime

Make sure Microsoft Edge WebView2 Runtime is installed (usually already available on Windows 10/11).

---

### Build Instructions

1. Open **MSYS2 MinGW64 terminal**

2. Navigate to project folder:

```
cd /c/path/to/BookStoreManager
```

3. Build for Windows:

```
make windows
```

4. Run the program:

```
./NhaSachFetel.exe
```

---

### Notes

- Always use **MSYS2 MinGW64 terminal**, not the default MSYS terminal.
- If `make` is not recognized, ensure you installed `mingw-w64-x86_64-make`.
- If missing `.dll` errors occur, run `make package` to bundle required files.

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

## Documentation

For detailed documentation of the system, please refer to the file below:

- [Project Documentation (PDF)](doc/BookStoreManager_Documentation.pdf)

## Author

Nguyen Hoang Minh Quoc <br>
Pham Quoc Trung <br>
Pham Mai Dieu Thao <br>
Pham Thai Cam Nhung <br>
