# Banking Management System

This **Banking Management System (BMS)** is a simple, console-based application built in **C++**. It helps manage customer accounts, transactions, withdrawals, and displays account details. Account information is stored in text files for persistence, ensuring no loss of data between program executions.

---

## Features

- **Create New Account**  
  Register a new customer account with the following details:
  - Account number
  - Account balance
  - Password
  - First name
  - Last name  
  Data is stored in a persistent file for future access.

- **View Account Details**  
  View the balance and details of an existing account by verifying the correct PIN.

- **Transactions**  
  Transfer money from one account to another.

- **Withdraw Funds**  
  Withdraw funds from an account after PIN verification.

- **PIN Verification**  
  For security, users must enter a correct PIN to view their account details or perform any transaction. Users have three attempts to enter the correct PIN.

All account details and transaction records are stored in files (`accountdetails.txt` and `transactiondetails.txt`) to ensure data persistence between program executions.

---

## File Structure

- **Files:**
  - `accountdetails.txt`: Stores account details for each user (account number, balance, password, first name, last name).
  - `transactiondetails.txt`: Stores transaction details (from account, to account, amount transferred).

- **Code File:**
  - `main.cpp`: Contains the full implementation of the Banking Management System, including functions for creating accounts, displaying account details, handling transactions, and withdrawals.

---

## How to Use

1. **Run the program** and select an option from the menu:
   - **Option 1**: Create a new account.
   - **Option 2**: If you already have an account, you can:
     - **A**: View account balance.
     - **B**: Make a transaction (transfer funds).
     - **C**: Withdraw funds from your account.
   - **Option 3**: Exit the program.

2. **Creating an Account**:
   - Enter your account number, initial balance, and set a password for your account.
   - The account will be stored in `accountdetails.txt`.

3. **Account Verification**:
   - To access account details or perform transactions, enter your account number and PIN.
   - If the PIN is correct, you will be allowed to view your balance or perform the selected operation.

4. **Transactions**:
   - To transfer money, enter the sending account number, the receiving account number, and the amount to transfer.
   - A successful transfer will update the account balances and store the transaction in `transactiondetails.txt`.

5. **Withdrawals**:
   - Enter the account number and the amount to withdraw.
   - Withdrawals are allowed only if sufficient funds are available in the account.

---

## Code Overview

### Core Structures

1. **`account_details`**  
   Stores user account information:
   - `account_no`: Unique identifier for the account.
   - `account_balance`: Current balance of the account.
   - `password`: A password for accessing the account.
   - `fname`: First name of the account holder.
   - `sname`: Last name of the account holder.

2. **`transaction_details`**  
   Stores details of each transaction:
   - `from_account`: The account number from which money is transferred.
   - `to_account`: The account number to which money is transferred.
   - `amount`: The amount being transferred.

---

### Main Functions

1. **`acc_details()`**  
   - Displays the account balance for the specified account number after PIN verification.

2. **`transaction()`**  
   - Transfers funds between two accounts, ensuring sufficient balance is available.

3. **`withdrawal()`**  
   - Allows the user to withdraw a specified amount from the account, ensuring sufficient funds are available.

4. **`PIN()`**  
   - Verifies the user's PIN and grants access to account details or allows transactions.
   - The user has three attempts to enter the correct PIN.

5. **`create_account()`**  
   - Allows users to create a new account and saves the account details to `accountdetails.txt`.

---

## Requirements

### Software

- **C++ Compiler**  
  - Example: GCC, Clang, or MSVC.

### System Requirements

- Operating System: Windows, macOS, or Linux.
- Minimum 2 GB RAM (recommended for smoother execution).

### Knowledge

- Basic understanding of:
  - C++ syntax and programming.
  - File handling in C++ (e.g., reading and writing files).
  - Console-based application interaction.

### Files

- Ensure the following files are in the same directory as the compiled executable:
  - `accountdetails.txt`: Used to store account details such as account number, balance, password, and user information.
  - `transactiondetails.txt`: Used to record transaction details between accounts.  
  *(These files will be created automatically if they don’t exist.)*

---

## Sample Usage

1. **Create an Account**:
   - Enter details such as first name, last name, account number, initial balance, and set a password.
   - The account will be stored in the `accountdetails.txt` file.

2. **Transactions**:
   - Enter your account number, the recipient's account number, and the amount to transfer.
   - The transfer will update both accounts and be logged in the `transactiondetails.txt` file.

3. **Withdrawals**:
   - Enter your account number and the amount you wish to withdraw, ensuring you have sufficient balance.

---

## Code File

- **`main.cpp`**  
  This file contains the main logic of the Banking Management System, including:
  - Functions for creating accounts and managing transactions.
  - File operations to persist account and transaction data.
