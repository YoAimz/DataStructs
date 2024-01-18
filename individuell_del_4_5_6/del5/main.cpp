//bankomat map
#include <iostream>
#include <map>
#include <string>

class BankAccountManager {
private:
    std::map<std::string, double> bank_account;
    std::string currentAccount;

public:
    void createBankAccount() {
        std::string accountNumber;
        double startBalance;

        std::cout <<"Type Account number: ";
        std::cin>> accountNumber;

        std::cout <<"Type starting balance: ";
        std::cin>> startBalance;

        bank_account[accountNumber] = startBalance;
        std::cout <<"Account has been created\n";
    }

    std::string login() {
        std::string accountNumber;

        std::cout <<"Type Account number: ";
        std::cin>> accountNumber;

        if (bank_account.find(accountNumber) != bank_account.end()) {
            currentAccount = accountNumber;
            std::cout <<"Logged in to account: " << currentAccount << ".\n";
        } 
        else {
            std::cout <<"Account number not found\n";
        }
        return currentAccount;
    }

    void deposit() {
        double moneyDeposit;
        std::cout <<"Type amount of money to deposit: ";
        std::cin>> moneyDeposit;

        bank_account[currentAccount] += moneyDeposit;
        std::cout <<moneyDeposit <<" sek has been added to the account. New account balance " <<bank_account[currentAccount] << " sek.\n";
    }

    void withdraw() {
        double moneyWithdraw;

        std::cout <<"Type amount of money to withdraw: ";
        std::cin>> moneyWithdraw;

        if (moneyWithdraw <= bank_account[currentAccount]) {
            bank_account[currentAccount] -= moneyWithdraw;
            std::cout <<moneyWithdraw <<" sek has been taken out from the account. New account balance: " <<bank_account[currentAccount] <<" sek.\n";
        } 
        else {
            std::cout <<"Not enough savings, please try again!\n";
        }
    }

    void printBankAccounts() {
        std::cout <<"\nBank Accounts:\n";
        for (const auto& entry : bank_account) {
            std::cout <<"Account: " <<entry.first <<"  Balance: " <<entry.second <<" sek\n";
        }
        std::cout <<"\n";
    }

    void displayAccountOptions() {
        std::cout <<"\nEnter option\n";
        std::cout <<"1. Deposit\n";
        std::cout <<"2. Withdraw\n";
        std::cout <<"3. Show Balance\n";
        std::cout <<"4. Logout\n";
    }

    void runBankingSystem() {
        int choice;

        while (true) {
            std::cout <<"Enter option\n";
            std::cout <<"1. Create account\n";
            std::cout <<"2. Log in\n";
            std::cout <<"3. End\n";
            std::cout <<"\n0. Display Bank Accounts\n";
            std::cin>> choice;

            switch (choice) {
                case 0:
                    printBankAccounts();
                    break;
                case 1:
                    createBankAccount();
                    break;
                case 2:
                    currentAccount = login();
                    break;
                case 3:
                    std::cout <<"BYE!\n";
                    return;
                default:
                    std::cout <<"Invalid option. Try again.\n";
                    continue;
            }

            if (!currentAccount.empty()) {
                while (true) {
                    displayAccountOptions();
                    std::cout <<"Enter option\n";
                    std::cin>> choice;

                    switch (choice) {
                        case 1:
                            deposit();
                            break;
                        case 2:
                            withdraw();
                            break;
                        case 3:
                            std::cout <<"Account Balance: " <<bank_account[currentAccount] <<" sek\n";
                            break;
                        case 4:
                            currentAccount = "";
                            std::cout <<"Logged out.\n";
                            break;
                        default:
                            std::cout <<"Invalid option. Try again.\n";
                            continue;
                    }
                    break;  
                }
            }
        }
    }
};

int main() {
    BankAccountManager bankManager;
    bankManager.runBankingSystem();

    return 0;
}
