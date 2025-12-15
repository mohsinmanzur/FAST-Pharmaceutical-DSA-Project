# 🏥 FastPharma - Pharmacy Management System

![C++](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows)
![Concept](https://img.shields.io/badge/Focus-Data_Structures-green?style=for-the-badge)

**FastPharma** is a comprehensive, console-based application designed to streamline the operations of a modern pharmacy. Built entirely in C++, this project demonstrates the practical application of advanced **Data Structures and Algorithms (DSA)** to handle inventory, billing, and employee records efficiently.

---

## 🚀 Key Features

### 👨‍💼 Admin Panel
* **Secure Authentication:** Password-protected login system for administrators.
* **Inventory Control:** Add new medicines, update stock levels, and manage pricing.
* **Staff Management:** Register new employees, set salaries, and define access levels (Admin/Employee).
* **Database Viewing:** View all registered employees and current medicine stock in real-time.

### 🛒 Customer Interface
* **Smart Search:** Instantly find medicines by name using optimized search algorithms.
* **Shopping Cart:** Add items, view current selections, and modify quantities before checkout.
* **Billing System:** Automated total calculation, change generation, and receipt simulation.
* **Purchase History:** Retrieve previous transaction details using a unique identifier (Phone Number).

### 💾 Data Persistence
* **File Handling:** The system uses binary file handling (`.dat` files) to ensure that Inventory, Employee Records, and Transaction Logs are saved permanently and retrieved upon relaunch.

---

## 🧠 Data Structures Used

This project was engineered to demonstrate the specific use cases of different data structures:

| Component | Data Structure | Implementation Details |
| :--- | :--- | :--- |
| **Medicine Inventory** | **Binary Search Tree (BST)** | Used for $O(\log n)$ search complexity, allowing for rapid lookup of medicines by name during billing. |
| **Shopping Cart** | **Stack** | Implements LIFO (Last-In, First-Out) logic to manage items added to the cart, facilitating easy removal of the most recent additions. |
| **Employee Records** | **Doubly Linked List** | Enables dynamic memory allocation for staff records, allowing efficient traversal (Next/Prev) and management of employee data. |
| **Transaction Logs** | **Binary File I/O** | Utilizes `fstream` for persistent storage of transaction history. |

---

## 🛠️ Tech Stack

* **Language:** C++ (Standard 11+)
* **Libraries:** `<iostream>`, `<fstream>`, `<vector>`, `<conio.h>`
* **IDE:** Visual Studio / DevC++
* **Platform:** Windows (Console Application)

---

**Author**: Muhammad Mohsin

**University**: National University of Computing and Emerging Sciences
