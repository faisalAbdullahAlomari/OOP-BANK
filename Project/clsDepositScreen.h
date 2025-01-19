#pragma once
#include <iostream>
#include "clsScreen.h"

using namespace std;


class clsDepositScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient Client){
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.getAccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber() {

        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        cin >> AccountNumber;
        
        return AccountNumber;
    }

public:
    static void ShowDepositScreen() {

        _DrawScreenHeader("\t   Deposit Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nClient With Account Number [" << AccountNumber << "] Does Not Exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease Enter Deposit Amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre You Sure You Want To Perform This Transaction? Y/N: ";
        char Answere = 'n';
        cin >> Answere;

        if (toupper(Answere) == 'Y') {

            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "New Balance Is: " << Client.AccountBalance;
        }
        else {

            cout << "\nOperation Was Cancelled.\n";
        }
    }
};

