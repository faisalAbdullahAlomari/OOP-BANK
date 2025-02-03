#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsCurrencyListScreen.h"

using namespace std;

class clsCurrencyMainScreen : protected clsScreen
{
private:

    enum enCurrencyMenuOptions {
        enListCurrencies = 1,
        enFindCurrency = 2,
        enUpdateRate = 3,
        enCurrencyCalc = 4,
        enMainMenu = 5
    };

    static short _ReadCurrencyMenuOption() {

        short Choise = 0;

        cout << setw(37) << left << "" << "Choose What Do You Want To Do [1 - 5]: ";
        Choise = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter A Number Between 1 to 5: ");

        return Choise;
    }

    static void _ShowListCurrenciesScreen(){
    
        //cout << "List Currencies Screen Will Be Here...";
        clsCurrencyListScreen::PrintCurrencyList();
    }

    static void _ShowFindCurrencyScreen() {

        cout << "Find Curreny Screen Will Be Here...";
    }

    static void _ShowUpdateCurrenyScreen() {

        cout << "Update Currency Screen Will Be Here...";
    }

    static void _ShowCurrencyCalcScreen() {

        cout << "Currency Calculator Screen Will Be Here...";
    }

    static void _GoBackToCurrenciesMainScreen() {

        cout << "\n\nPress Any Key To Go Back To Currencies Main Screen...\n";
        system("pause>0");
        ShowCurrencyMainScreen();
    }

    static void _PerformCurrencyMenuOption(enCurrencyMenuOptions enCurrencyMenuOption) {

        switch (enCurrencyMenuOption) {
        case enCurrencyMenuOptions::enListCurrencies:
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrenciesMainScreen();
            break;

        case enCurrencyMenuOptions::enFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMainScreen();
            break;

        case enCurrencyMenuOptions::enUpdateRate:
            system("cls");
            _ShowUpdateCurrenyScreen();
            _GoBackToCurrenciesMainScreen();
            break;

        case enCurrencyMenuOptions::enCurrencyCalc:
            system("cls");
            _ShowCurrencyCalcScreen();
            _GoBackToCurrenciesMainScreen();
            break;

        case enCurrencyMenuOptions::enMainMenu:
        {
            // This Will Take The User Automatically Back To The Main Menu...
        }
        }
    }

public:

	static void ShowCurrencyMainScreen() {
		
		system("cls");

		_DrawScreenHeader("\tCurrency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformCurrencyMenuOption((enCurrencyMenuOptions)_ReadCurrencyMenuOption());

	}
};

