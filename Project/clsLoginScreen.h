#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{

private:

	static bool _Login() {

		bool LoginFailed = false;
		short FailedLoginCount = 0;

		string Username, Password;

		do {

			if (LoginFailed) {

				FailedLoginCount++;

				cout << "\nInvalid Username/Password!\n\n";
				cout << "\nYou Have " << (3 - FailedLoginCount) << " Tria(s) To Login.\n\n";
			}

			if (FailedLoginCount == 3) {

				cout << "\nYou Are Locked After 3 Failed trials.\n\n";
				return false;
			}

			cout << "Enter Username: ";
			cin >> Username;

			cout << "Enter Password: ";
			cin >> Password;

			CurrentUser = clsUser::Find(Username, Password);

			LoginFailed = CurrentUser.IsEmpty();
		} while (LoginFailed);
		
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenu();

		return true;
	}

	void _Log() {

	}

public:

	static bool ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\t Login Screen");

		return _Login();
	}
};