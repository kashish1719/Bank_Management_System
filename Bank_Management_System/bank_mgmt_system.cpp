#include<iostream>
#include<string>
#include<fstream>
#include<vector> 

using namespace std;

void Red(){cout<<"\033[1;31m";}
void Green(){cout<<"\033[1;32m";}
void Yellow(){cout<<"\033[1;33m";}
void Blue(){cout<<"\033[1;34m";}
void Magenta(){cout<<"\033[1;35m";}
void Cyan(){cout<<"\033[1;36m";}
void Reset(){cout<<"\033[0m";}

class bankAccount{
    private:
        string bankName = "KBOI";
        int bankCode;
        string accountHolderName;
        string accountNumber;
        string accountPassword;
        string aadharNumber;
        string email;
        string phoneNumber;
        double balance;
        vector<string> transactionHistory;
    public:
        void savetoFile();
        void loadFromFile();
        void mainMenu();
        void createAccount();
        void loginBankAccount();
        void depositMoney();
        void withdrawMoney();
        void checkBalance();
        void accountDetails();
        void allTransactionsHistory();
};

// saving data to file
void bankAccount::savetoFile(){
    ofstream file(accountNumber + ".txt");

    if(file.is_open()){
        file << accountHolderName << endl;
        file << accountNumber << endl;
        file << accountPassword << endl;
        file << aadharNumber << endl;
        file << email << endl;
        file << phoneNumber << endl;
        file << balance << endl;

        for(auto transaction : transactionHistory){
            file<<transaction<<endl;
        }
        file.close();
    } else{
        cout<<"Error opening file for writing!"<<endl;
    }
}

// reading / loading data from file
void bankAccount::loadFromFile(){
    ifstream file(accountNumber + ".txt");

    if(file.is_open()){
        getline(file, accountHolderName);
        getline(file, accountNumber);
        getline(file, accountPassword);
        getline(file, aadharNumber);
        getline(file, email);
        getline(file, phoneNumber);
        file>>balance;
        // Ignore the newline after balance
        file.ignore();

        string transaction;
        while(getline(file, transaction)){
            transactionHistory.push_back(transaction);
        }
        file.close();
    } else{
        cout<<"Error opening file for reading!"<<endl;
    }
}

// Main Menu
void bankAccount::mainMenu(){
    int choice;
    do{
        cout<<"======================================"<<endl;
        cout<<"Welcome to "<<bankName<<" Bank!"<<endl;
        cout<<"Enter 1 to Deposit Money"<<endl;
        cout<<"Enter 2 to Withdraw Money"<<endl;
        cout<<"Enter 3 to Check Balance"<<endl;
        cout<<"Enter 4 to get Account Details"<<endl;
        cout<<"Enter 5 to  view All Transactions History"<<endl;
        cout<<"Enter 6 to Logout"<<endl;
        cout<<"======================================"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        // Ignore the newline character after choice input
        cin.ignore();
        // Clear the console screen
        system("cls");

        switch(choice){
            case 1:
                depositMoney();
                break;
            case 2:
                withdrawMoney();
                break;
            case 3:
                checkBalance();
                break;
            case 4:
                accountDetails();
                break;
            case 5:
                allTransactionsHistory();
                break;
            case 6:
                cout<<"Logging out..."<<endl;
                return; // Exit the main menu
            default:
                cout<<"Invalid choice! Please try again."<<endl;
        }
    }
    while(choice != 6);
}

// Create Account
void bankAccount::createAccount(){
    Green();
    cout<<"    Create Account    "<<endl;
    cout<<"======================================"<<endl;
    cout<<"Enter Account Holder Full Name: ";
    getline(cin, accountHolderName);
    // cout<<"Enter Account Number: ";
    // getline(cin, accountNumber);
    cout<<"Enter Email Id: ";
    getline(cin, email);
    cout<<"Enter Phone Number: ";
    getline(cin, phoneNumber);
    cout<<"Enter Aadhar Number: ";
    getline(cin, aadharNumber);
    cout<<"Enter Account Password: ";
    getline(cin, accountPassword);
    cout<<"======================================"<<endl;
    Reset();

    balance = 500.0;
    ifstream file("Kashish-Bank-Of-India.txt");
    if(file.is_open()){
        file>>bankCode;
        file.close();
        ofstream output("Kashish-Bank-Of-India.txt");
        if(output.is_open()){
            output<<bankCode + 1;
            output.close();
        } else{
            cout<<"Error opening file!"<<endl;
        }
    } else{
        cout<<"Error opening file!"<<endl;
    }
    accountNumber = bankName + to_string(bankCode);
    transactionHistory.push_back("Deposit: " + to_string(balance));

    Yellow();
    cout<<"Account created successfully!"<<endl;
    cout<<"Your Account Number is: "<<accountNumber<<endl;
    cout<<"Account Password is: "<<accountPassword<<endl;
    cout<<"Minimum balance of Rs. 500 has been credited to your account."<<endl;
    cout<<"======================================"<<endl;
    Reset();
    savetoFile();
}

// Login to Bank Account
void bankAccount::loginBankAccount(){
    string enteredAccountNumber, enteredPassword;
    Blue();

    cout<<"    Login to Your Account    "<<endl;
    cout<<"======================================"<<endl;
    cout<<"Enter Account Number: ";
    getline(cin, enteredAccountNumber);

    ifstream file(enteredAccountNumber + ".txt");
    if(file.is_open()){
        accountNumber = enteredAccountNumber;
        loadFromFile();
        cout<<"Enter Account Password: ";
        getline(cin, enteredPassword);
        if(accountPassword == enteredPassword){
            Green();
            cout<<"Login Successful!"<<endl;
            Reset();
            mainMenu();
        } else{
            Red();
            cout<<"Invalid Password!"<<endl;
            Reset();
        }
        file.close();
    } else{
        cout<<"Account with this number does not exist!"<<endl;
    }
    
}

// Deposit Money
/*
void bankAccount::depositMoney(){
    double amount;
    cout<<"Enter amount to deposit: ";
    cin>>amount;
    cin.ignore();

    if(amount > 0){
        balance += amount;
        transactionHistory.push_back("Deposit: " + to_string(amount));
        ofstream file(accountNumber + ".txt", ios::app);

        if(file.is_open()){
            Green();
            cout<<"Amount deposited successfully!"<<endl;
            Reset();
            cout<<"New Balance: Rs. "<<balance<<endl;
            file<<"Deposit: " + to_string(amount)<<endl;
            file.close();
        } else{
            cout<<"Deposit Not Successful!"<<endl;
        }
    }
    else{
        Red();
        cout<<"Invalid Amount!."<<endl;
        Reset();
    }
}
*/

// updated Deposit
void bankAccount::depositMoney(){
    double amount;

    cout<<"Enter amount to deposit: ";
    cin>>amount;
    cin.ignore();

    if(amount > 0){

        balance += amount;

        transactionHistory.push_back(
            "Deposit: " + to_string(amount)
        );

        // Save updated data
        savetoFile();

        Green();
        cout<<"Amount deposited successfully!"<<endl;
        Reset();

        cout<<"New Balance: Rs. "<<balance<<endl;
    }
    else{
        Red();
        cout<<"Invalid Amount!"<<endl;
        Reset();
    }
}

// Withdraw Money
/*
void bankAccount:: withdrawMoney(){
    double amount;
    cout<<"Enter amount to withdraw: ";
    cin>>amount;
    cin.ignore();

    if(amount > 0 && amount <= balance){
        balance -= amount;
        transactionHistory.push_back("Withdraw: " + to_string(amount));
        ofstream file(accountNumber + ".txt", ios::app);
        if(file.is_open()){
            Green();
            cout<<"Amount withdrawn successfully!"<<endl;
            Reset();
            cout<<"New Balance: Rs. "<<balance<<endl;
            file<<"Withdraw: " + to_string(amount)<<endl;
            file.close();
        } else{
            cout<<"Withdrawal Not Successful!"<<endl;
        }
    }
    else{
        Red();
        cout<<"Invalid amount or insufficient balance!"<<endl;
        Reset();
    }
}
*/

// updated Withdraw
void bankAccount::withdrawMoney(){
    double amount;

    cout<<"Enter amount to withdraw: ";
    cin>>amount;
    cin.ignore();

    if(amount > 0 && amount <= balance){

        balance -= amount;

        transactionHistory.push_back(
            "Withdraw: " + to_string(amount)
        );

        // Save updated data
        savetoFile();

        Green();
        cout<<"Amount withdrawn successfully!"<<endl;
        Reset();

        cout<<"New Balance: Rs. "<<balance<<endl;
    }
    else{
        Red();
        cout<<"Invalid amount or insufficient balance!"<<endl;
        Reset();
    }
}

// Check Balance
void bankAccount::checkBalance(){
    Cyan();
    cout<<"======================================"<<endl;
    cout<<"Your Current Balance is: Rs. "<<balance<<endl;
    cout<<"======================================"<<endl;
    Reset();
}

// Account Details
void bankAccount::accountDetails(){
    Magenta();
    cout<<"======================================"<<endl;
    cout<<"|         Kashish Bank Of India      |"<<endl;
    cout<<"======================================"<<endl;
    Blue();

    cout<<"Account Holder Name: "<<accountHolderName<<endl;
    cout<<"Account Number: "<<accountNumber<<endl;
    cout<<"Email Id: "<<email<<endl;
    cout<<"Phone Number: "<<phoneNumber<<endl;
    cout<<"Aadhar Number: "<<aadharNumber<<endl;
    cout<<"Your Current Balance is: Rs. "<<balance<<endl;
    cout<<"======================================"<<endl;
    Reset();
}

// All Transactions History
void bankAccount::allTransactionsHistory(){
    Yellow();
    cout<<"======================================"<<endl;
    cout<<"|      All Transactions History      |"<<endl;
    cout<<"======================================"<<endl;
    cout<<"Account Holder Name: "<<accountHolderName<<endl;
    cout<<"Account Number: "<<accountNumber<<endl;
    for(const auto& transaction : transactionHistory){
        cout<<transaction<<endl;
    }
    cout<<"======================================"<<endl;
    Reset();
}

int main(){
    // Object of bankAccount class
    bankAccount account;
    int choice;
    do{
        cout<<"======================================"<<endl;
        cout<<"Welcome to Kashish Bank Of India!"<<endl;
        cout<<endl;
        cout<<"Enter 1 to Create Account"<<endl;
        cout<<"Enter 2 to Login to Your Account"<<endl;
        cout<<"Enter 3 to Exit"<<endl;
        cout<<"======================================"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        cin.ignore();
        system("cls");
        
        switch(choice){
            case 1:
                account.createAccount();
                break;
            case 2:
                account.loginBankAccount();
                break;
            case 3:
                cout<<"Thank you for using Kashish Bank Of India. Goodbye!"<<endl;
                break;
            default:
                cout<<"Invalid choice! Please try again."<<endl;
        }
    } while(choice != 3);
    
    return 0;
}
