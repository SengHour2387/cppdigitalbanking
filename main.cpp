#include <iostream>
#include "user.h"
#include "console.h"
#include "bank.h"
using namespace std;

int main() {
    Bank bank = Bank();
    BankConsole::displayMenu();
    return 0;
}