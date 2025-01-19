#pragma once
#include <iostream>
#include "clsScreen.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:

	static void _PrintUser(clsUser User) {

		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}

public:
	
	static void _ShowDeleteUserScreen() {

		_DrawScreenHeader("\t Delete User Screen");

		string Username = "";

		cout << "\nEnter Username: ";
		Username = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(Username)) {

			cout << "\nUser Is Not Found, Choose Another One: ";
			Username = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(Username);
		_PrintUser(User);

		cout << "\nAre You Sure You Want To Delete This User? Y/N: ";
		char Answere = 'n';
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			if (User.Delete()) {

				cout << "\nUser Deleted Succefully :-)\n";
				_PrintUser(User);
			}
			else {

				cout << "\nError User Was Not Deleted\n";
			}
		}
	}
};

