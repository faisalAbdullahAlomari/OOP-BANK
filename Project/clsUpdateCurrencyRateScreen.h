#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:

	static float _ReadRate() {

		cout << "\nEnter New Rate: ";
		float NewRate = 0;

		NewRate = clsInputValidate::ReadFloatNumber();
		return NewRate;
	}

	static void _PrintCurrency(clsCurrency Currency) {

		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry : " << Currency.GetCountry();
		cout << "\nCode    : " << Currency.GetCurrencyCode();
		cout << "\nName    : " << Currency.GetCurrencyName();
		cout << "\nRate($1): " << Currency.GetRate();
	}

public:

	static void ShowUpdateCurrencyRateScreen() {

		_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = "";

		cout << "\nPlease Enter Currency Code: ";
		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

			cout << "\nCurrency Is Not Found, Choose Another One: ";
			clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		cout << "\nAre You Sure You Want To Update This Currency? Y/N: ";
		char Answere = 'n';
		cin >> Answere;

		if (toupper(Answere) == 'Y') {

			cout << "\nUpdate Currency Rate:";
			cout << "_____________________________\n";
			
			Currency.UpdateRate(_ReadRate());

			cout << "\nCurrency Rate Updated Successfully :-)";
			_PrintCurrency(Currency);
		}
	}
};

