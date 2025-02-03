#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <vector>
#include "clsCurrency.h"

using namespace std;

class clsCurrencyListScreen : protected clsScreen
{
private:

	static void PrintCurrencyRecordLine(clsCurrency Currency) {

		cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.GetCountry();
		cout << "| " << setw(8) << left << Currency.GetCurrencyCode();
		cout << "| " << setw(45) << left << Currency.GetCurrencyName();
		cout << "| " << setw(10) << left << Currency.GetRate();
	}

public:

	static void PrintCurrencyList() {

		vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

		string title = "\tCurrencies List Screen";
		string body = "\t    (" + to_string(vCurrencies.size()) + ") Currency.";

		_DrawScreenHeader(title, body);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate/(1$)";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;

		if (vCurrencies.size() == 0) {

			cout << "\t\t\t\tNo Currencies Available In The System!";
		}
		else {

			for (clsCurrency Currency : vCurrencies) {

				PrintCurrencyRecordLine(Currency);
				cout << endl;
			}
		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_______________________________________________\n" << endl;
	}
};

