#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewUserScreen : protected clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User) {

		cout << "\nEnter First Name: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permissions: ";
		User.Permissions = _ReadPermissionsToSet();
	}

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

	static int _ReadPermissionsToSet() {

		int Permissions = 0;
		char Answere = 'n';

		cout << "\nDo You Want To Give Full Access? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			return -1;
		}

		cout << "\nDo You Want To Give Access to:\n";

		cout << "\nShow Client List? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pTransactions;
		}

		cout << "\nManage Users? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pManageUsers;
		}
		
		cout << "\nShow Login Register? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pLoginRegister;
		}

		cout << "\nCurrency Exchange Menu? Y/N: ";
		cin >> Answere;
		if (toupper(Answere) == 'Y') {

			Permissions += clsUser::enPermissions::pCurrencyMainScreen;
		}

		return Permissions;
	}

public:

	static void ShowAddNewUserScreen() {

		_DrawScreenHeader("\t Add New User Screen");

		string UserName = "";

		cout << "\nPlease Enter Username: ";
		UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName)) {

			cout << "\nUsername Is Already Used, Choose Another One: ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResults;

		SaveResults = NewUser.Save();

		switch (SaveResults) {
		case clsUser::enSaveResults::svSucceeded:
			cout << "\nUser Added Successfully :-)\n";
			_PrintUser(NewUser);
			break;

		case clsUser::enSaveResults::svFailedEmptyObject:
			cout << "\nError User Was Not Saved Because It's Empty";
			break;

		case clsUser::enSaveResults::svFailedUserExists:
			cout << "\nError, User Was Not Saved Because Username Is Used!\n";
			break;
		}
	}
};

