# NotinOOP - Course Project #06
**Object-Oriented Programming (Practicum) Course @ FMI, Sofia University** **2025/2026**

## Project Overview
"NotinOOP" is a console-based application that simulates an online perfume store, integrating the core processes of modern e-commerce platforms. The system allows for comprehensive management of users, a product catalog, orders, inventory, and various types of discounts, providing a realistic digital shopping environment. It features role-based access control, a smart recommendation engine, a review system, and persistent file-based data storage.

## Author
* **Name:** Ivaylo Shopov
* **Faculty Number:** 2MI0600565
* **Major:** Software Engineering
* **Faculty:** Faculty of Mathematics and Informatics, Sofia University

---

## Features
- **Role-Based Access Control:** Supports two types of users: Buyers (customers) and Administrators (managers), each with specific permissions.
- **Shopping Experience:** Buyers can browse fragrances, maintain a shopping cart, add funds to their balance, and manage a wishlist of favorite products.
- **Order Management:** Tracks the complete lifecycle of purchases with statuses: `PENDING`, `DELIVERED`, or `CANCELED`. 
- **Recommendation Engine:** Analyzes a buyer's wishlist to determine their favorite fragrance note (family) and suggests 3 random perfumes with the same note.
- **Review & Moderation System:** Buyers can leave ratings (0-5) and comments. Admins can moderate and remove reviews. Users with 7+ removed reviews are automatically blocked.
- **Polymorphic Discount System:** Automatically applies the best available discount during checkout. Supports:
  - *Standard Discount:* Percentage off.
  - *Bonus Discount:* Percentage off plus a fixed amount deduction.
  - *Brand Discount:* Percentage off exclusively for specific brands.
- **Data Persistence:** The system state (users, fragrances, orders, reviews, discounts) is automatically loaded upon startup and saved to a file-based database upon exit.

---

## Command Reference

### Global Commands
| Command | Argument | Description |
| :--- | :--- | :--- |
| `register` | `[username] [password]` | Registers a new user in the system. |
| `login` | `[username] [password]` | Logs into an existing account. |
| `logout` | - | Logs out the current user. |
| `help` | - | Displays available commands based on the user's role. |
| `end` | - | Saves the current state to the database and exits. |

### Buyer Commands
| Command | Argument | Description |
| :--- | :--- | :--- |
| `add-to-balance` | `[amount]` | Adds funds to the buyer's account balance. |
| `add-to-wishlist` | `[fragrance-name]` | Adds a perfume to the wishlist. |
| `remove-from-wishlist`| `[fragrance-name]` | Removes a perfume from the wishlist. |
| `add-to-cart` | `[fragrance-name]` | Adds a perfume to the shopping cart. |
| `remove-from-cart`| `[fragrance-name]` | Removes a perfume from the shopping cart. |
| `view-cart` | - | Displays the current contents of the shopping cart. |
| `checkout` | - | Finalizes the purchase, applying the best discount if available. |
| `view-bought` | - | Shows a history of successfully delivered purchases. |
| `view-purchases` | - | Shows a complete history of all purchases (Pending, Delivered, Canceled). |
| `cancel` | `[purchase-id]` | Cancels a pending order and refunds the balance. |
| `make-review` | `[name] [rating] [comment]`| Leaves a review (0-5 rating) for a specific fragrance. |
| `recommend` | - | Suggests 3 new perfumes based on the most common note in the wishlist. |

### Administrator Commands
| Command | Argument | Description |
| :--- | :--- | :--- |
| `create-fragrance`| `[name] [brand] [price] [note]`| Adds a new fragrance to the store catalog. |
| `add-quantity` | `[name] [quantity]` | Restocks the inventory of a specific perfume. |
| `deliver` | `[purchase-id]` | Updates an order's status from PENDING to DELIVERED. |
| `remove-review` | `[frag-id] [review-id]` | Deletes a review (auto-blocks user if 7+ removed). |
| `block-user` | `[username]` | Manually blocks a user and deletes their account. |

---

## Technical Details
- **Architecture:** Built strictly on Object-Oriented Programming principles (Encapsulation, Inheritance, Polymorphism). Utilizes advanced Design Patterns (Command Pattern for input handling, Visitor Pattern for operations).
- **Memory Management:** Extensive use of Modern C++ smart pointers (`std::shared_ptr`, `std::unique_ptr`, `std::weak_ptr`) to ensure memory safety and prevent leaks. Move semantics (`std::move`) are used for performance optimization.
- **Standard Library:** Leverages the C++ Standard Template Library (STL) including `std::vector`, `std::string`, and `<algorithm>` for data processing and filtering.
- **Validation:** Implements robust exception handling to catch invalid arguments and command syntax errors without crashing the application.

---

## How to Run
1. Compile the source files using a C++ compiler (VC++, GCC, or Clang) with C++14/C++17 support.
2. Run the generated executable.
3. The system will attempt to load the `system_data.txt` file. If not found, it will start with a fresh database.
4. Type `help` to see available commands or `register` to create your first account.

## License
This project is licensed under the [MIT License](https://github.com/IvayloShopov33/NotinOOP/blob/master/LICENSE.txt).
