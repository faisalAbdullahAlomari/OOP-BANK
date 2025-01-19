#pragma once
#include <iostream>
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client){
	
		cout << "\nClient Card:";
		cout << "\n_________________________________";
		cout << "\nFirst Name     : " << Client.FirstName;
		cout << "\nLast Name      : " << Client.LastName;
		cout << "\nFull Name      : " << Client.FullName();
		cout << "\nEmail          : " << Client.Email;
		cout << "\nPhone          : " << Client.Phone;
		cout << "\nAccount Number : " << Client.getAccountNumber();
		cout << "\nPin Code       : " << Client.PinCode;
		cout << "\nAccount Balance: " << Client.AccountBalance;
		cout << "\n_________________________________";
	}

public:
	
	static void ShowDeleteClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {

			return;//this will exit the function ans it will not continue
		}

		_DrawScreenHeader("\tDelete Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber)) {

			cout << "\nAccount Number Is Not Found!, Choose Another One";
			AccountNumber = clsInputValidate::ReadString();
		}
		
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		cout << "\nAre You Sure You Want To Delete This Client? Y/N: ";
		char Answere = 'n';
		cin >> Answere;

		if (toupper(Answere) == 'Y') {

			if (Client.Delete()) {

				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client);
			}
			else {

				cout << "\nError, Client Was Not Deleted!";
			}
		}

	}
};

