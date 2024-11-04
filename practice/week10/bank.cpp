#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    double balance;
    string accountHolderName;

public:
    // 생성자
    BankAccount(string name, double initialBalance)
        : accountHolderName(name), balance(initialBalance) {}

    // 현재 잔액 조회 메서드
    double getBalance() const {
        return balance;
    }

    // 입금 메서드
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << amount << " deposited. Current balance: " << balance << endl;
        }
    }

    // 출금 메서드
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << amount << " withdrawn. Current balance: " << balance << endl;
        } else {
            cout << "Insufficient balance or invalid amount!" << endl;
        }
    }
};

int main() {
    // 계좌 생성
    BankAccount myAccount("Alice", 1000);
    // 잔액 조회 (public 메서드를 통해 접근)
    cout << "Initial Balance: " << myAccount.getBalance() << endl;
    // 입금 및 출금 (public 메서드를 통해 접근)
    myAccount.deposit(500);
    myAccount.withdraw(200);

    return 0;
}
