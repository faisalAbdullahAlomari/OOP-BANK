#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
#include "clsLoginRegisterScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
	
private:

	enum enMainMenuOptions {
		enListClients = 1,
		enAddNewClient = 2,
		enDeleteClient = 3,
		enUpdateClient = 4,
		enFindClient = 5,
		enTransactionsMenu = 6,
		enManageUsers = 7,
		enLoginRegister = 8,
		enExit = 9
	};

	static short _ReadMainMenuOption() {

		cout << setw(37) << left << "" << "Choose What Do You Want To Do [1 - 9]: ";
		short Choise = clsInputValidate::ReadShortNumberBetween(1, 9, "Enter Short Number Between 1 To 9: ");
		
		return Choise;
	}

	static void _ShowAllClientsScreen() {

		/*cout << "\nClient List Screen Will Be Here...\n";*/
		clsClientListScreen::ShowClientsList();
	}

	static void _GoBackToMainMenu() {

		cout << setw(37) << left << "" << "\n\tPress Any Key To Go Back To Main Menu...\n";
		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowAddNewClientScreen() {

		//cout << "\nAdd New Client Screen Will Be Here...\n";
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen() {

		//cout << "\nDelete Client Screen Will Be Here...\n";
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen() {

		//cout << "\nUpdate Client Screen Will Be Here...\n";
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen() {

		//cout << "\nFind Client Screen Will Be Here...\n";
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionMenu() {

		//cout << "\nTransaction Menu Will Be Here...\n";
		clsTransactionsScreen::ShowTransactionsMenue();
	}

	static void _ShowManageUsersMenu() {

		//cout << "\nManage Users Menu Will Be Here...\n";
		clsManageUsersScreen::ShowManageUsersMenu();
	}

	/*static void _ShowEndScreen() {

		cout << "\nEnd Screen Will Be Here...\n";
	}*/

	static void _ShowLoginRegisterScreen() {

		//cout << "Login Register Screen Will Be Here...\n";
		clsLoginRegisterScreen::ShowLoginRegisterScreen();

	}

	static void _Logout() {

		CurrentUser = clsUser::Find("", "");
	}

	static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption) {

		switch (MainMenuOption) {
		case enMainMenuOptions::enListClients:
			system("cls");
			_ShowAllClientsScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enAddNewClient:
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enDeleteClient:
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enUpdateClient:
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enFindClient:
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enTransactionsMenu:
			system("cls");
			_ShowTransactionMenu();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enManageUsers:
			system("cls");
			_ShowManageUsersMenu();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enLoginRegister:
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;

		case enMainMenuOptions::enExit:
			system("cls");
			_Logout();
			break;
		}
	}

public:

	static void ShowMainMenu() {

		system("cls");
		_DrawScreenHeader("\t\tMain Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
		cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
		cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
		cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find Client.\n";
		cout << setw(37) << left << "" << "\t[6] Transactions.\n";
		cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
		cout << setw(37) << left << "" << "\t[8] Login Register.\n";
		cout << setw(37) << left << "" << "\t[9] Logout.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}
};