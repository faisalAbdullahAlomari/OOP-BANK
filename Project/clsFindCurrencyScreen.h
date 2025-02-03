#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:

	static void _PrintCurrency(clsCurrency Currency) {

		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry : " << Currency.GetCountry();
		cout << "\nCode    : " << Currency.GetCurrencyCode();
		cout << "\nName    : " << Currency.GetCurrencyName();
		cout << "\nRate($1): " << Currency.GetRate();
		cout << "_____________________________\n";
	}

	static void _ShowResult(clsCurrency Currency) {

		if (!Currency.IsEmpty()) {

			cout << "Currency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else {

			cout << "\nCurrency Was Not Found :-(\n";
		}
	}

public:
	static void ShowFindCurrencyScreen() {

		short Number = 0;
		string CurrencyCode = "";

		cout << "Find By: [1] Code Or [2] Country: ";
		cin >> Number;

		if (Number == 1) {

			cout << "Please Enter Currency Code: ";
			CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResult(Currency);
		}
		else{

			string Country = "";
			cout << "\nPlease Enter Country Name: ";
			Country = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(Country);
			_ShowResult(Currency);
		}
	}
};

