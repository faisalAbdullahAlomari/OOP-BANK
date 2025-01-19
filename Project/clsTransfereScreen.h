#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsTransfereScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client) {

		cout << "\nClient Card:";
		cout << "\n_______________________\n";
		cout << "\nFull Name      : " << Client.FullName();
		cout << "\nAccount Number : " << Client.getAccountNumber();
		cout << "\nAccount Balance: " << Client.getAccountBalance();
		cout << "\n_______________________\n";
	}

	static string _ReadAccountNumber(string Transfer) {

		string AccountNumber;

		cout << "\nEnter Account Number To Transfer " << Transfer << ": ";

		AccountNumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount Number Is Not Found, Choose Another One: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		return AccountNumber;
	}

	static float ReadAmount(clsBankClient SourceClient) {

		float Amount;

		cout << "\nEnter Transfere Amount: ";

		Amount = clsInputValidate::ReadFloatNumber();

		while (Amount > SourceClient.AccountBalance) {

			cout << "\nAmount Exceeds The Available Balance, Enter Another Amount: ";
			Amount = clsInputValidate::ReadDblNumber();
		}

		return Amount;
	}

public:

	static void ShowTransfereScreen() {

		_DrawScreenHeader("\t Transfere Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("From"));

		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("To"));

		_PrintClient(DestinationClient);

		float Amount = ReadAmount(SourceClient);

		cout << "\nAre You Sure You Want To Perform This Operation? Y/N: ";
		char Answere = 'n';
		cin >> Answere;

		if (toupper(Answere)) {

			if (SourceClient.Transfere(Amount, DestinationClient)) {

				cout << "\nTransfere Done Successfully.\n";
			}
			else {

				cout << "\nTransfere Failed.\n";
			}
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);
	}
};

