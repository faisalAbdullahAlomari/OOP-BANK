#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:

    enum enManageUsersMenuOptions {
        enListUsers = 1,
        enAddNewUser = 2,
        enDeleteUser = 3,
        enUpdateUser = 4,
        enFindUser = 5,
        enMainMenu = 6
    };

    static short _ReadManageUsersMenuOption() {

        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1 - 6]: ";
        short Choise = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between [1 - 6]");
        
        return Choise;
    }

    static void _GoBackToManageUsersMenu() {

        cout << "\n\nPress Any Key To Go Back To Manage Users Menu...";
        system("pause>0");
        ShowManageUsersMenu();
    }

    static void _ShowListUsersScreen() {

        //cout << "\nList Users Screen Will Be Here.\n";
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUsersScreen() {

        //cout << "\nAdd New User Screen Will Be Here.\n";
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }

    static void _ShowDeleteUsersScreen() {

        //cout << "\nDelete User Screen Will Be Here.\n";
        clsDeleteUserScreen::_ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen() {

        //cout << "\nUpdate User Screen Will Be Here.\n";
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen() {

        //cout << "\nFind User Screen Will Be Here.\n";
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _PerformManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption) {

        switch (ManageUsersMenuOption) {

        case enManageUsersMenuOptions::enListUsers:
            system("cls");
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::enAddNewUser:
            system("cls");
            _ShowAddNewUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::enDeleteUser:
            system("cls");
            _ShowDeleteUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::enUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::enFindUser:
            system("cls");
            _ShowAddNewUsersScreen();
            _GoBackToManageUsersMenu();
            break;

        case enManageUsersMenuOptions::enMainMenu:

            //do nothing here the main screen will handle it :-)
            break;
        }
    }

public:

	static void ShowManageUsersMenu() {

        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers)) {

            return;//this will exit the function ans it will not continue
        }

        system("cls");
        _DrawScreenHeader("\t Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUsersMenuOption((enManageUsersMenuOptions)_ReadManageUsersMenuOption());
	}
};