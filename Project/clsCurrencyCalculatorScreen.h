#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
	static float _ReadAmount() {

		float Amount = 0;

		cout << "Enter Currency1 Amount: ";
		cin >> Amount;

		return Amount;
	}

	static clsCurrency _GetCurrency(string Message) {

		string CurrencyCode = "";

		cout << Message << endl;

		CurrencyCode = clsInputValidate::ReadString();

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {

			cout << "\nCurrency Is Not Found, Choose Another One: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;
	}

	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:\n") {

		cout << "\n" << Title << endl;
		cout << "_____________________________\n";
		cout << "\nCountry : " << Currency.GetCountry();
		cout << "\nCode    : " << Currency.GetCurrencyCode();
		cout << "\nName    : " << Currency.GetCurrencyName();
		cout << "\nRate($1): " << Currency.GetRate();
		cout << "_____________________________\n";
	}

	static void _PrintCalculationsResults(float Amount, clsCurrency From, clsCurrency To) {

		_PrintCurrencyCard(From, "Convert From: ");

		float AmountInUSD = From.ConvertToUSD(Amount);

		cout << Amount << " " << From.GetCurrencyCode() << " = " << AmountInUSD << " USD\n";

		if (To.GetCurrencyCode() == "USD") {

			return;
		}

		cout << "\nConverting From USD To:\n";
		_PrintCurrencyCard(To, "To: ");

		float AmountInCurrency2 = From.ConvertToOtherCurrency(Amount, To);

		cout << Amount << " " << From.GetCurrencyCode() << " = " << AmountInCurrency2 << " " << To.GetCurrencyCode();
	}

public:

	static void ShowCurrencyCalculatorScreen() {

		char Continue = 'y';

		while (toupper(Continue) == 'Y') {

			system("cls");

			_DrawScreenHeader("\tUpdate Currency Screen");

			clsCurrency ConvertFrom = _GetCurrency("\nEnter Currency1 Code: ");
			clsCurrency ConvertTo = _GetCurrency("\nEnter Currency2 Code: ");
			float Amount = _ReadAmount();

			_PrintCalculationsResults(Amount, ConvertFrom, ConvertTo);

			cout << "\n\nDo You Want To Perform Another Calculation? Y/N: ";
			cin >> Continue;
		}
	}
};

