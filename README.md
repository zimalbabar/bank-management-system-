# Banking Management System

This **Banking Management System (BMS)** is a simple, console-based application built in **C++**. It helps manage customer accounts, transactions, deposits, withdrawals, and donations. Account information and transaction records are stored in text files for persistence, ensuring no data loss between program executions.


## Features

- **Create New Account**: Register accounts with unique details stored in `account.txt`.
- **View Account Details**: Access account balance and details with PIN verification.
- **Deposit/Withdraw Funds**: Manage funds securely.
- **Donate Funds**: Transfer money to a donation account.
- **Transactions**: Transfer funds between accounts.
- **PIN Security**: Verifies PIN with three attempts for secure access.

---

## File Structure

- `account.txt`: Stores account details.
- `deposit.txt`: Logs deposits.
- `withdrawal.txt`: Logs withdrawals.
- `donation.txt`: Records donations.
- `main.cpp`: Contains all code for account management and transactions.

---

## How to Use

1. **Run the Program**:
   - Choose actions like creating an account, viewing balance, depositing, withdrawing, or donating.
2. **Account Management**:
   - Create accounts by entering details like name, PIN, and initial balance.
   - Securely verify PIN for transactions or viewing balances.
3. **Transactions**:
   - Deposit, withdraw, or transfer funds between accounts, with updates logged in respective files.
4. **Donations**:
   - Donate funds to charitable causes, logged in `donation.txt`.

---

## Key Functions

1. **`acc_details()`**: Displays account balance post PIN verification.
2. **`create_account()`**: Creates and stores new accounts in `account.txt`.
3. **`transaction()`**: Transfers funds between accounts.
4. **`deposit()`**: Logs deposits in `deposit.txt`.
5. **`withdrawal()`**: Logs withdrawals in `withdrawal.txt`.
6. **`donation()`**: Handles donations and logs them in `donation.txt`.

---

## Requirements

- **Software**: Any C++ compiler (e.g., GCC, Clang).
- **Files**: The following will be generated/used:
  - `account.txt`, `deposit.txt`, `withdrawal.txt`, `donation.txt`.

---

## Sample Usage

1. **Create an Account**: Enter account details like name, PIN, and initial balance.
2. **Transactions**: Transfer funds between accounts, ensuring sufficient balance.
3. **Deposits/Withdrawals**: Add or remove money from accounts securely.
4. **Donations**: Donate to specified causes with recipient and amount logged.

---

## Code File

- **`main.cpp`**: The core file implementing account management, transactions, and file operations.

---

## Future Enhancements

1. Add a graphical user interface (GUI) for better usability.  
2. Support multi-currency accounts and currency conversion.  
3. Include account activity reports and detailed logs.  
4. Implement online banking features with enhanced security.  
5. Add features like interest calculation and admin management tools.  

