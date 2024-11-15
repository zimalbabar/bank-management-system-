# Banking Management System

This **Banking Management System (BMS)** is a simple, console-based application built in **C++**. It helps manage customer accounts, transactions, deposits, withdrawals, and donations. Account information and transaction records are stored in text files for persistence, ensuring no data loss between program executions.

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

- **Deposit Funds**  
  Deposit money into an account.

- **Withdraw Funds**  
  Withdraw money from an account, ensuring the user has sufficient balance.

- **Donate Funds**  
  Transfer funds to a donation account for charitable purposes.

- **Transactions**  
  Transfer money from one account to another.

- **PIN Verification**  
  For security, users must enter a correct PIN to view their account details or perform any transaction. Users have three attempts to enter the correct PIN.

All account details and transaction records are stored in files (`account.txt`, `deposit.txt`, `donation.txt`, and `withdrawal.txt`) to ensure data persistence between program executions.

---

## File Structure

- **Files:**
  - `account.txt`: Stores account details for each user (account number, balance, password, first name, last name).
  - `deposit.txt`: Records deposit transactions (account number, amount deposited, date/time).
  - `donation.txt`: Records donations (account number, amount donated, recipient).
  - `withdrawal.txt`: Records withdrawal transactions (account number, amount withdrawn, date/time).

- **Code File:**
  - `main.cpp`: Contains the full implementation of the Banking Management System, including functions for creating accounts, displaying account details, handling transactions, deposits, withdrawals, and donations.

---

## How to Use

1. **Run the program** and select an option from the menu:
   - **Option 1**: Create a new account.
   - **Option 2**: If you already have an account, you can:
     - **A**: View account balance.
     - **B**: Make a deposit into the account.
     - **C**: Make a withdrawal from the account.
     - **D**: Donate funds to a charitable cause.
     - **E**: Make a transaction (transfer funds).
   - **Option 3**: Exit the program.

2. **Creating an Account**:
   - Enter your account number, initial balance, and set a password for your account.
   - The account will be stored in `account.txt`.

3. **Account Verification**:
   - To access account details or perform transactions, enter your account number and PIN.
   - If the PIN is correct, you will be allowed to view your balance or perform the selected operation.

4. **Deposits**:
   - To deposit funds into your account, specify the amount to deposit.
   - The deposit will be logged in the `deposit.txt` file.

5. **Withdrawals**:
   - To withdraw funds from your account, specify the amount to withdraw.
   - Withdrawals will be recorded in the `withdrawal.txt` file.

6. **Donations**:
   - To donate funds to a charitable organization, specify the donation amount and recipient.
   - Donations will be recorded in the `donation.txt` file.

7. **Transactions**:
   - To transfer funds between accounts, specify the sending account number, receiving account number, and amount to transfer.
   - The transaction will be recorded in the appropriate files and account balances will be updated.

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

3. **`deposit_details`**  
   Stores details of deposit transactions:
   - `account_no`: The account number receiving the deposit.
   - `deposit_amount`: The amount deposited.
   - `deposit_date`: The date/time of the deposit.

4. **`withdrawal_details`**  
   Stores details of withdrawal transactions:
   - `account_no`: The account number from which money is withdrawn.
   - `withdrawal_amount`: The amount withdrawn.
   - `withdrawal_date`: The date/time of the withdrawal.

5. **`donation_details`**  
   Stores details of donations:
   - `account_no`: The account number making the donation.
   - `donation_amount`: The amount donated.
   - `donation_recipient`: The recipient of the donation.

---

### Main Functions

1. **`acc_details()`**  
   - Displays the account balance for the specified account number after PIN verification.

2. **`transaction()`**  
   - Transfers funds between two accounts, ensuring sufficient balance is available.

3. **`deposit()`**  
   - Allows the user to deposit a specified amount into their account.

4. **`withdrawal()`**  
   - Allows the user to withdraw a specified amount from their account, ensuring sufficient funds are available.

5. **`donation()`**  
   - Allows the user to donate a specified amount to a charitable cause or recipient.

6. **`PIN()`**  
   - Verifies the user's PIN and grants access to account details or allows transactions.
   - The user has three attempts to enter the correct PIN.

7. **`create_account()`**  
   - Allows users to create a new account and saves the account details to `account.txt`.

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
  - `account.txt`: Used to store account details such as account number, balance, password, and user information.
  - `deposit.txt`: Used to record deposit transactions.
  - `donation.txt`: Used to record donations.
  - `withdrawal.txt`: Used to record withdrawal transactions.  
  *(These files will be created automatically if they don’t exist.)*

---

## Sample Usage

1. **Create an Account**:
   - Enter details such as first name, last name, account number, initial balance, and set a password.
   - The account will be stored in the `account.txt` file.

2. **Transactions**:
   - Enter your account number, the recipient's account number, and the amount to transfer.
   - The transfer will update both accounts and be logged in the `transaction.txt` file.

3. **Deposits**:
   - Enter the amount to deposit into your account.
   - The deposit will be recorded in the `deposit.txt` file.

4. **Withdrawals**:
   - Enter the amount to withdraw from your account, ensuring sufficient funds.
   - Withdrawals will be recorded in the `withdrawal.txt` file.

5. **Donations**:
   - Enter the amount to donate and the recipient.
   - Donations will be recorded in the `donation.txt` file.

---

## Code File

- **`main.cpp`**  
  This file contains the main logic of the Banking Management System, including:
  - Functions for creating accounts, managing transactions, handling deposits, withdrawals, and donations.
  - File operations to persist account and transaction data.

