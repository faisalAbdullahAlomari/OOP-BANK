#pragma once
#include <iostream>
#include "clsScreen.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client) {

        {
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
	}

    static string _ReadAccountNumber() {

        string AccountNumber = "";

        cout << "\nEnter Account Number: ";
        cin >> AccountNumber;

        return AccountNumber;
    }

public:

    static void ShowWithdrawScreen() {

        _DrawScreenHeader("\t   Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExist(AccountNumber)) {

            cout << "\nClient With Account Number [" << AccountNumber << "] Does Not Exist, Enter Another One: ";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nEnter Withdraw Amount: ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre You Sure You Want To Perform This Transaction? Y/N: ";
        char Answere = 'n';
        cin >> Answere;

        if (toupper(Answere) == 'Y') {

            if (Client.Withdraw(Amount)) {

                cout << "\nAmount Withdraw Successfully.\n";
                cout << "\nNew Balance Is: " << Client.AccountBalance;
            }
            else {

                cout << "\nCannot Wihtdraw, Insuffecient Balance!\n";
                cout << "\nAmount to Withdraw Is: " << Amount;
                cout << "\nYour Balance Is: " << Client.AccountBalance;
            }
        }
    }
};

