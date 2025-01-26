
#include<iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"

using namespace std;

static void _PrintCurrency(clsCurrency Currency) {

	cout << "\nCurrency Card:\n";
	cout << "_____________________________\n";
	cout << "\nCountry      : " << Currency.GetCountry();
	cout << "\nCode         : " << Currency.GetCurrencyCode();
	cout << "\nCurrency Name: " << Currency.GetCurrencyName();
	cout << "\nRate(1$)     = " << Currency.GetRate();
	cout << "\n_____________________________\n";
}

int main() {

	/*while (true) {
		
		if (!clsLoginScreen::ShowLoginScreen()) {
			break;
		}
	}*/

	clsCurrency	Currency = Currency.FindByCode("jod");

	if (Currency.IsEmpty()) {

		cout << "\nCurrency Is Not Found!\n";
	}
	else {

		_PrintCurrency(Currency);
	}

	clsCurrency Currency2 = Currency.FindByCountry("Egypt");

	if (Currency.IsEmpty()) {

		cout << "Currency Is Not Found!\n";
	}
	else {

		_PrintCurrency(Currency2);
	}

	cout << "Currency After Updating Rate:\n";
	Currency.UpdateRate(0.71);
	_PrintCurrency(Currency);

	return 0;
}