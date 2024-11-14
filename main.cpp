#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Base class
class Account
{
protected:
    string accountNumber;
    string accountHolderName;
    string acctype;
    int pin;
    double balance;

public:
    Account() {}
    Account(string accNum, string holderName, int pass, double initialBalance)
        : accountNumber(accNum), accountHolderName(holderName), pin(pass), balance(initialBalance) {}

    virtual ~Account() {}

    void setaccountHolderName(string newHolderName)
    {
        accountHolderName = newHolderName;
    }
    string getacctype()
    {
        return acctype;
    }
    int getpin()
    {
        return pin;
    }
    void display()
    {
        cout << accountNumber << endl
             << accountHolderName << endl
             << balance << endl
             << pin;
    }

    bool authenticate(const string &filepath, const string &accNum, int pin1)
    {
        ifstream inFile(filepath, ios::in);
        if (inFile.is_open())
        {
            // string line;
            string lineAccountNumber;
            string lineAccountName;
            string linePin;
            string lineBla;
            string linetype;
            while (true)
            {
                getline(inFile, lineAccountNumber);
                if (lineAccountNumber == "")
                {
                    break;
                };

                getline(inFile, lineAccountName);
                getline(inFile, linePin);
                getline(inFile, lineBla);
                getline(inFile, linetype);

                if (accNum == lineAccountNumber && std::to_string(pin1) == linePin)
                {
                    accountNumber = lineAccountNumber;
                    accountHolderName = lineAccountName;
                    pin = stoi(linePin);
                    balance = stoi(lineBla);
                    acctype = linetype;
                    inFile.close();
                    return true;
                }
            }
            inFile.close();
        }
        return false;
    }

    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    virtual void deposit(int passkey, double amount)
    {
        if (this->pin == passkey)
        {
            balance += amount;
            cout<<"\nDeposit Successfull";
            cout<<"\nNew Balance: "<<balance;
            update(this->accountNumber,this->accountHolderName,this->pin);
            saveToFile();
        }
        else
        {
            cout << "Deposit Failed";
            return;
        }

        time_t now = time(0);
        string deposit_time = ctime(&now);
        ofstream outFile("deposit.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << accountNumber << endl;
            outFile << accountHolderName << endl;
            outFile << pin << endl;
            outFile << balance << endl;
            outFile << deposit_time;
            outFile << amount << endl;
            outFile.close();
            cout << "Deposit details saved to file." << endl;
        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    }

    virtual void withdraw(int passkey, double amount)
    {
        if (this->pin == passkey)
        {
            if (balance >= amount)
            {
                balance -= amount;

                update(this->accountNumber,this->accountHolderName,this->pin);
                saveToFile();
            }
            else
            {
                cout << "Insufficient funds." << endl;
            }
        }
        else
        {
            cout << "Withdrawal Failed";
        }
        time_t now = time(0);
        string withdrawal_time = ctime(&now);
        ofstream outFile("withdrawal.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << accountNumber << endl;
            outFile << accountHolderName << endl;
            outFile << pin << endl;
            outFile << balance << endl;
            outFile << withdrawal_time;
            outFile << amount << endl;
            outFile.close();
            cout << "Withdrawal details saved to file." << endl;

        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    }

    virtual void viewDetails() const
    {
        cout << "Account Number: " << accountNumber
             << "\nAccount Holder: " << accountHolderName
             << "\nPin: " << pin
             << "\nBalance: " << balance << endl;
    }

    // Save account details to a file
    virtual void saveToFile() const
    {
        ofstream outFile("account.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << accountNumber << endl;
            outFile << accountHolderName << endl;
            outFile << pin << endl;
            outFile << balance << endl;
            outFile << "CURRENT" << endl;
            outFile.close();
            cout << "Account details saved to file." << endl;
        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    }

    // Retrieve account details from a file
    void retrieveFromFile()
    {
        ifstream inFile("account.txt", ios::app);
        if (inFile.is_open())
        {
            getline(inFile, accountNumber);
            getline(inFile, accountHolderName);
            inFile >> pin;
            inFile >> balance;
            inFile >> acctype;
            inFile.ignore();
            inFile.close();
            cout << "Account details retrieved from file." << endl;
        }
        else
        {
            cout << "Error opening file for reading." << endl;
        }
    }
    void update(string inputAccountNumber,string inputAccountHolderName,int inputAccountpin)
    {

        // Check if the account details match
        ifstream inFile("account.txt");
        if (inFile.is_open())
        {
            string fileAccountNumber;
            string fileAccountHolderName;
            string fileAccountType;
            int fileAccountpin;
            double fileBalance;

            ofstream tempFile("temp_account.txt"); // Temporary file

            while (getline(inFile, fileAccountNumber))
            {
                getline(inFile, fileAccountHolderName);
                inFile >> fileAccountpin;
                inFile >> fileBalance;
                inFile >> fileAccountType;
                inFile.ignore(); // Ignore the newline character after reading the balance

                // If the current entry doesn't match the account to be deleted, write it to the temporary file
                if (!(inputAccountNumber == fileAccountNumber && inputAccountpin == fileAccountpin))
                {
                    tempFile << fileAccountNumber << endl;
                    tempFile << fileAccountHolderName << endl;
                    tempFile << fileAccountpin << endl;
                    tempFile << fileBalance << endl;
                }
            }

            inFile.close();
            tempFile.close();

            // Remove the original file
            remove("account.txt");

            // Rename the temporary file to the original file
            rename("temp_account.txt", "account.txt");

        }
        else
        {
            cout << "Error updating account details." << endl;
        }
    }


    static void viewAccountHistory(const string &accNum, int passkey)
    {
        string accNumber, accHname, withdrawal_t, dep_t;
        double bal, amount;
        int pin;

        ifstream file("withdrawal.txt");
        if (!file.is_open())
        {
            cout << "Unable to open file for reading withdrawal history" << endl;
            return;
        }

        cout << "Withdrawal History for Account Number: " << accNum << endl;
        while (getline(file, accNumber))
        {
            file >> ws;
            getline(file, accHname);
            file >> pin;
            file >> bal;
            file >> ws;
            getline(file, withdrawal_t);
            file >> amount;
            if (accNum == accNumber && passkey == pin)
            {
                cout << "Account Number: " << accNum
                     << "\nAccount Holder: " << accHname
                     << "\nPin: " << pin
                     << "\nBalance Before: " << bal
                     << "\nWithdrawal Time: " << withdrawal_t
                     << "\nAmount Withdrawn: " << amount
                     << "\nBalance After: " << bal - amount << endl;
            }
        }

        file.close();

        ifstream file1("deposit.txt");
        if (!file1.is_open())
        {
            cout << "Unable to open file for reading deposit history" << endl;
            return;
        }

        cout << "Deposit History for Account Number: " << accNum << endl;
        while (getline(file1, accNumber))
        {
           // file1 >> ws;
            getline(file, accHname);
            file1 >> pin;
            file1 >> bal;
            file1 >> ws;
            getline(file1, dep_t);
            file1 >> amount;
            if (accNum == accNumber && passkey == pin)
            {
                cout << "Account Number: " << accNum
                     << "\nAccount Holder: " << accHname
                     << "\nAccount Pin: " << pin
                     << "\nBalance Before: " << bal
                     << "\nDeposit Time: " << dep_t
                     << "\nAmount Withdrawn: " << amount
                     << "\nBalance After: " << bal + amount << endl;
            }
        }

        file1.close();
    }



    void donations(int donate_amount)
    {   if(balance<donate_amount)
       {
        cout<<"Your current balance wont allow this donation to take place";
       }
        cout<<"\nTHANK YOU FOR SUPPORTING THIS CHARITY\n";
        balance-=donate_amount;
        update(this->accountNumber,this->accountHolderName,this->pin);
        saveToFile();

        //saving donations in file
        ofstream donation("donation.txt", ios::app);
        if (!donation.is_open())
        {
            cout << "Unable to open file for writing donation history" << endl;
            return;
        }

       donation << accountNumber << endl << accountHolderName << endl <<donate_amount <<endl<<"END"<<endl;

       donation.close();

    }

    friend class Transactions;

    void delAccount()
    {
        string inputAccountNumber;
        string inputAccountHolderName;
        int inputAccountpin;
        cout << "Enter your account number: ";
        cin >> inputAccountNumber;
        cout << "Enter your account pin: ";
        cin >> inputAccountpin;
        cin.ignore(); // Ignore leftover newline from previous input
        cout << "Enter your name: ";
        getline(cin, inputAccountHolderName);

        // Check if the account details match
        ifstream inFile("account.txt");
        if (inFile.is_open())
        {
            string fileAccountNumber;
            string fileAccountHolderName;
            string fileAccountType;
            int fileAccountpin;
            double fileBalance;

            ofstream tempFile("temp_account.txt"); // Temporary file

            while (getline(inFile, fileAccountNumber))
            {
                getline(inFile, fileAccountHolderName);
                inFile >> fileAccountpin;
                inFile >> fileBalance;
                inFile >> fileAccountType;
                inFile.ignore(); // Ignore the newline character after reading the balance

                // If the current entry doesn't match the account to be deleted, write it to the temporary file
                if (!(inputAccountNumber == fileAccountNumber && inputAccountpin == fileAccountpin))
                {
                    tempFile << fileAccountNumber << endl;
                    tempFile << fileAccountHolderName << endl;
                    tempFile << fileAccountpin << endl;
                    tempFile << fileBalance << endl;
                }
            }

            inFile.close();
            tempFile.close();

            // Remove the original file
            remove("account.txt");

            // Rename the temporary file to the original file
            rename("temp_account.txt", "account.txt");

            cout << "Account successfully deleted." << endl;
        }
        else
        {
            cout << "Error opening file for reading." << endl;
        }
    }

    // Operator overloading for output
    friend istream &operator>>(istream &is, Account &account)
    {
        cout << "Enter Account Number: ";
        is >> account.accountNumber;
        cout << "Enter Account Holder Name: ";
        is >> account.accountHolderName;
        cout << "Enter Account Type: ";
        is >> account.acctype;
        cout << "Enter Pin: ";
        is >> account.pin;
        cout << "Enter Balance: ";
        is >> account.balance;
        return is;
    }
    friend ostream &operator<<(ostream &os, const Account &account)
    {
        os << "Account Number: " << account.accountNumber << endl;
        os << "Account Holder Name: " << account.accountHolderName << endl;
        os << "Account Type: " << account.acctype << endl;
        os << "Balance: " << account.balance << endl;
        os << "Pin: " << account.pin << endl;
        return os;
    }
};

// Derived class
class SavingsAccount : public Account
{
private:
    double interestRate;

public:
    SavingsAccount() {}
    SavingsAccount(string accNum, string holderName, int pass, double initialBalance, double interest)
        : Account(accNum, holderName, pass, initialBalance), interestRate(interest) { applyInterest();}

    double calculateInterest()
    {
        return balance * interestRate / 100;
    }

    void applyInterest()
    {
        balance += calculateInterest();
    }

    void saveToFile() const override
    {
        ofstream outFile("account.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << accountNumber << endl;
            outFile << accountHolderName << endl;
            outFile << pin << endl;
            outFile << balance << endl;
            outFile << "SAVINGS" << endl;
            outFile.close();
            cout << "Account details saved to file." << endl;
        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    }

    void viewDetails() const override
    {
        Account::viewDetails();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};
class StudentAccount : public Account
{
private:
    static double overdraft_limit;

public:
    StudentAccount() {}
    StudentAccount(string account_number, string accountholder, int pass, double balance = 0)
        : Account(account_number, accountholder, pass, balance) {  }

    virtual void saveToFile() const
    {
        ofstream outFile("account.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << accountNumber << endl;
            outFile << accountHolderName << endl;
            outFile << pin << endl;
            outFile << balance << endl;
            outFile << "STUDENT" << endl;
            outFile.close();
            cout << "Account details saved to file." << endl;
        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    }

    void withdraw(int pin, double amount) override
    {
        int pass;
        cout << "\nEnter Pin:";
        cin >> pass;
        if (this->pin == pass)
        {
            if (balance + overdraft_limit >= amount)
            {
                balance -= amount;
                cout << "Withdrew " << amount << ". New balance is " << balance << endl;
                update(this->accountNumber,this->accountHolderName,this->pin);
                saveToFile();
            }
            else
            {
                cout << "Exceeds overdraft limit." << endl;
            }
        }
        else
        {
            cout << "Withdrawal Failed";
        }
        time_t now = time(0);
        string withdrawal_time = ctime(&now);
        ofstream outFile("withdrawal.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << accountNumber << endl;
            outFile << accountHolderName << endl;
            outFile << pin << endl;
            outFile << balance << endl;
            outFile << withdrawal_time;
            outFile << amount << endl;
            outFile.close();
            cout << "Withdrawal details saved to file." << endl;

        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    
    }
};
double StudentAccount::overdraft_limit = 1000;

class ChildSavingsAccount : public Account
{
private:
    // double daily_limit;
    // double withdrawn_today;
    string guardian_name;

public:
    ChildSavingsAccount() {}
    ChildSavingsAccount(string account_number, string accountholder,  int pass,double bal, string guardian)
        : Account(account_number, accountholder, pass, bal), guardian_name(guardian) {}

    virtual void saveToFile() const
    {
        ofstream outFile("account.txt", ios::app);
        if (outFile.is_open())
        {
            outFile << accountNumber << endl;
            outFile << accountHolderName << endl;
            outFile << pin << endl;
            outFile << balance << endl;
            outFile << "CHILD" << endl;
            outFile.close();
            cout << "Account details saved to file." << endl;
        }
        else
        {
            cout << "Error opening file for writing." << endl;
        }
    }

    void withdraw(int pin, double amount) override
    {
        cout << "\nThis type of Account doesn't offer withdrawal services.\n";
        cout << "\nFor more information contact our helpline";
    }
};

class Transactions
{
private:
    string transaction_time;
    static int transactionID;
    string sourceAccount;
    string destinationAccount;
    double amount;
    string date;
    string transactionType;

public:
    int getTransactionID() const { return transactionID; }
    string getSourceAccount() const { return sourceAccount; }
    string getDestinationAccount() const { return destinationAccount; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }
    string getTransactionType() const { return transactionType; }

    void transactions(string &toAccountnum, string &fromAccountnum, int pin, double amount)
    {
        transactionID++;
        Account toAccount, fromAccount;
        ifstream inFile("./account.txt");

        if (!inFile.is_open())
        {
            cout << "Error opening file for reading." << endl;
            return;
        }

        string lineAccountNumber, lineAccountName, linePin, lineBalance, lineType;
        while (getline(inFile, lineAccountNumber))
        {
            getline(inFile, lineAccountName);
            getline(inFile, linePin);
            getline(inFile, lineBalance);
            getline(inFile, lineType);

            if (toAccountnum == lineAccountNumber)
            {
                toAccount.accountNumber = lineAccountNumber;
                toAccount.accountHolderName = lineAccountName;
                toAccount.pin = std::stoi(linePin);
                toAccount.balance = std::stod(lineBalance);
                toAccount.acctype = lineType;
            }

            if (fromAccountnum == lineAccountNumber)
            {
                fromAccount.accountNumber = lineAccountNumber;
                fromAccount.accountHolderName = lineAccountName;
                fromAccount.pin = std::stoi(linePin);
                fromAccount.balance = std::stod(lineBalance);
                fromAccount.acctype = lineType;
            }
        }
        inFile.close();

        if (fromAccount.pin != pin)
        {
            cout << "Transaction Failed due to incorrect pin" << endl;
            return;
        }
        if (toAccount.accountNumber == "")
        {
            cout << "Could not find transaction account" << endl;
            return;
        }


        if (fromAccount.balance < amount)
        {
            std::cout << "Error: Insufficient balance" << std::endl;
            return;
        }

        fromAccount.balance -= amount;
        toAccount.balance += amount;

        time_t now = time(0);
        string transaction_time = ctime(&now);
        this->date = transaction_time;
        this->sourceAccount = fromAccount.accountNumber;
        this->destinationAccount = toAccountnum;
        this->amount = amount;
        this->transactionType = "Transfer"; // by default it is transfer

        std::cout << "\nTransaction successful";
        std::cout << "\nTransaction Timing: " << transaction_time;

        SaveToFile();
    }

    void viewTransactionHistory(const string &accNum)
    {
        ifstream file("transaction.txt");
        if (!file.is_open())
        {
            cout << "Unable to open file for reading transaction history" << endl;
            return;
        }
        cout << "Transaction History for Account Number: " << accNum << endl;
        Transactions t;
        while (file >> t.transactionID)
        {
            getline(file, t.sourceAccount);
            getline(file, t.destinationAccount);
            file >> t.amount;
            file >> ws;
            getline(file, t.date);
            getline(file, t.transactionType);

            if (t.sourceAccount == accNum || t.destinationAccount == accNum)
            {
                cout << "Transaction ID: " << t.transactionID
                     << "\nSource Account: " << t.sourceAccount
                     << "\nDestination Account: " << t.destinationAccount
                     << "\nAmount: " << t.amount
                     << "\nDate: " << t.date
                     << "\nTransaction Type: " << t.transactionType << endl;
            }
        }

        file.close();
    }

    void generateAccountStatement(int pin, string accNum)
    {
        cout << "\nAccount Statements:\n";
        viewTransactionHistory(accNum);
        Account::viewAccountHistory(accNum, pin);
    }

    void SaveToFile()
    {
        ofstream file("transaction.txt", ios::app);
        if (file.is_open())
        {
            file << transactionID << endl;
            file << sourceAccount << endl;
            file << destinationAccount << endl;
            file << amount << endl;
            file << date << transactionType << endl;
            file << "END" << endl; // to mark the end of a transaction record
        }
        else
        {
            cout << "Unable to open file to save transaction data" << endl;
        }
    }
};
int Transactions::transactionID = 0;

void displayMainMenu()
{
    cout << "\nWelcome to the Banking System" << endl;
    cout << "1. Create Account" << endl;
    cout << "2. Login" << endl;
    cout << "3. Staff Login" << endl;
    cout << "4. Exit" << endl;
    cout << "Please choose an option: ";
}

void displayAccountMenu()
{
    cout << "\nAccount Menu" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. View Account Details" << endl;
    cout << "4. Delete Account" << endl;
    cout << "5. Transactions" << endl;
    cout << "6. View Account History" << endl;
    cout << "7. Donations" << endl;
    cout << "8. Logout" << endl;
    cout << "Please choose an option: ";
}
bool containsNumeric(const string &input) {
    for (char c : input) {
        if (isdigit(c)) {
            return true; // Numeric character found
        }
    }
    return false; // No numeric characters found
}

// Function to get valid string input from the user
string getValidStringInput() {
    string input;
    while (true) {
        getline(cin, input);
        if (!containsNumeric(input)) {
            break; // Valid input, exit loop
        } else {
            cout << "Input contains numeric values. Please try again." << endl;
        }
    }
    return input;
}
class USER: public Account {
public:
    string username;
    string password;
    int donationsraised;

    USER(string u, string p) : username(u), password(p) {}

    bool authenticate(string inputUser, string inputPass) {
        return (username == inputUser && password == inputPass);
    }
       void retrieveFromFile()
    { 
        string accountNumber,accountHolderName, acctype;
        int pin;
        double balance;
        int total_account;
        
       std::ifstream inFile("account.txt");

    if (inFile.is_open()) {
        while (getline(inFile, accountNumber)) {
            total_account++;
            getline(inFile, accountHolderName);
            inFile >> pin;
            inFile >> balance;
            inFile.ignore(); // To ignore the newline character after balance
            getline(inFile, acctype);

            // Print the values
            std::cout << "Account Number: " << accountNumber << std::endl;
            std::cout << "Account Holder Name: " << accountHolderName << std::endl;
            std::cout << "PIN: " << pin << std::endl;
            std::cout << "Balance: " << balance << std::endl;
            std::cout << "Account Type: " << acctype << std::endl;

            // Clear the input buffer for the next read
            inFile.ignore();
        }
        cout<<"Total Accounts Registered: "<<total_account;
        inFile.close();
    } else {
        std::cout << "Error opening file for reading." << std::endl;
    }
       
    }


    void donationhistory()
    {
        ifstream file;
        file.open("donation.txt",ios:: app );
        if (file.is_open())
        {  
            string donationuser,donatedamount,donated,donationholder;
            while(getline(file,donationuser)){
                if( donationuser == " ")  
                {   
                    break;

                }
                getline(file,donationholder);
                file>>ws;
                getline(file,donatedamount);
                getline(file,donated);
                file >> ws;

            cout<<"\nAccount NO "<<donationuser<<"\nAccount Name:"<<donationholder<<" DONATED "<<donatedamount<<" RS";
            donationsraised += stoi(donatedamount);
            cout << "\nAccount details retrieved from file." << endl;
        }
        }

        else
        {
            cout << "Error opening file for reading." << endl;
        }
        cout<<"\n"<<"Total donations raised = "<<donationsraised;
    }

};


int main()
{

    Account *currentAccount = nullptr;
    int choice;

    while (true)
    {
        displayMainMenu();
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nCreate Account\n";
            string accNum, holderName, acctype;
            int pin;
            double initialBalance;
         std::srand(std::time(0));

    // Generate and print random numbers

        int random_number = std::rand() % 10000 + 1; // Generates a number in the range 1 to 100
        

         accNum = to_string(random_number);

            // cout << "Enter Account Number: ";
            // cin >> accNum;
            cout<< "\nYour Account No is " << accNum;
            cout << "\nEnter Account Holder Name: ";
            cin.ignore();
           // getline(cin, holderName);
            holderName = getValidStringInput();
            cout << "Enter Account Type (SAVINGS or CURRENT or CHILD or STUDENTS): ";
            cin >> acctype;
            cout << "Enter Pin: ";
            cin >> pin;
            cout << "Enter Initial Balance: ";
            cin >> initialBalance;

            if (acctype == "SAVINGS")
            {
                double interestRate;
                cout << "Enter Interest Rate: ";
                cin >> interestRate;
                currentAccount = new SavingsAccount(accNum, holderName, pin, initialBalance, interestRate);
            }
            else if (acctype == "CHILD")
            {
                string guardian;
                cout << "Enter Guardian: ";
                cin >> guardian;
                currentAccount = new ChildSavingsAccount(accNum, holderName, pin, initialBalance, guardian);
            }
            else if (acctype == "STUDENTS")
            {
                currentAccount = new StudentAccount(accNum, holderName, pin, initialBalance);
            }

            else
            {
                currentAccount = new Account(accNum, holderName, pin, initialBalance);
            }

            currentAccount->saveToFile();
            delete currentAccount;
            currentAccount = nullptr;
        }
        else if (choice == 2)
        {
            cout << "\nLogin\n";
            string accNum;
            int pin;

            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Pin: ";
            cin >> pin;

            Account tempAccount;
            if (tempAccount.authenticate("./account.txt", accNum, pin))
            {
                cout<<"\nLOGIN SUCCESSFULL\n";
                if (tempAccount.getacctype() == "SAVINGS")
                {
                    currentAccount = new SavingsAccount(tempAccount.getAccountNumber(), tempAccount.getAccountHolderName(), tempAccount.getpin(), tempAccount.getBalance(), 0.0);
                }
                else if (tempAccount.getacctype() == "CHILD")
                {
                    currentAccount = new ChildSavingsAccount(tempAccount.getAccountNumber(), tempAccount.getAccountHolderName(), tempAccount.getpin(), tempAccount.getBalance(), "");
                }
                else if (tempAccount.getacctype() == "STUDENT")
                {
                    currentAccount = new StudentAccount(tempAccount.getAccountNumber(), tempAccount.getAccountHolderName(), tempAccount.getpin(), tempAccount.getBalance());
                }
                else
                {
                    currentAccount = new Account(tempAccount.getAccountNumber(), tempAccount.getAccountHolderName(), tempAccount.getpin(), tempAccount.getBalance());
                }

                int accountChoice;
                do
                {
                    displayAccountMenu();
                    cin >> accountChoice;

                    if (accountChoice == 1)
                    {
                        double amount;
                        cout << "Enter Amount to Deposit: ";
                        cin >> amount;
                        currentAccount->deposit(pin, amount);
                    }
                    else if (accountChoice == 2)
                    {
                        double amount;
                        cout << "Enter Amount to Withdraw: ";
                        cin >> amount;
                        currentAccount->withdraw(pin, amount);
                    }
                    else if (accountChoice == 3)
                    {
                        currentAccount->viewDetails();
                    }
                    else if (accountChoice == 4)
                    {
                        currentAccount->delAccount();
                    }
                    else if (accountChoice == 5)
                    {
                        Transactions t;
                        string accNum, dessNum;
                        int accpin;
                        double transferamount;
                        cout << "\nRe-enter your account number: ";
                        cin >> accNum;
                        cout << "\nRe-enter your pin: ";
                        cin >> accpin;
                        cout << "\nEnter destination account number: ";
                        cin >> dessNum;
                        cout << "\nEnter transfer amount: ";
                        cin >> transferamount;

                        t.transactions(dessNum, accNum, accpin, transferamount);
                    }
                    else if (accountChoice == 6)
                    {
                        Transactions t;
                        t.generateAccountStatement(pin, accNum);
                    }
                    else if (accountChoice == 7)
                    {
                        int donate;
                        cout<<"THANKS FOR CHOOSING THIS CHARITY ";
                        cin>>donate;
                        currentAccount->donations(donate);
                    }
                } while (accountChoice != 8);

                delete currentAccount;
                currentAccount = nullptr;
            }
            else
            {
                cout << "Invalid account number or pin." << endl;
            }
        }
        else if (choice == 3)
        {
            USER u1("admin","1234");
            string pass,role;
            cout<<"Enter role:";
            cin>>role;
            cout<<"Enter Pass:";
            cin>>pass;
            cout<<"LOGIN SUCCESSFULL";
            int user_ch;
            do{
            cout<<"\nPRESS 1 to see donation status: ";
            cout<<"\nPRESS 2 to see accounts status: ";
            cout<<"\nPRESS 3 to logout: ";
            
            cin>>user_ch;
            
            if(user_ch == 1){
            u1.authenticate(role,pass);
            u1.donationhistory();}
            if(user_ch==2)
            {
                u1.retrieveFromFile();
            }
           } while(user_ch != 3);

        }
        else if (choice == 4)
        {
            cout << "Exiting the system." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
