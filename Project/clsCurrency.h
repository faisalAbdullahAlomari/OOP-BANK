#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsCurrency
{
private:

	enum enMode {
		EmptyMode = 0,
		UpdateMode = 1
	};
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#") {

		vector<string> vCurrencyData;

		vCurrencyData = clsString::Split(Line, Separator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#") {

		string stCurrencyRecord = "";

		stCurrencyRecord += Currency.GetCountry() + Separator;
		stCurrencyRecord += Currency.GetCurrencyCode() + Separator;
		stCurrencyRecord += Currency.GetCurrencyName() + Separator;
		stCurrencyRecord += to_string(Currency.GetRate());

		return stCurrencyRecord;
	}

	static vector<clsCurrency> _LoadCurrenciesDataFromFile() {

		vector<clsCurrency> vCurrencies;

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return vCurrencies;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencies) {

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (MyFile.is_open()) {

			for (clsCurrency C : vCurrencies) {

				DataLine = _ConvertCurrencyObjectToLine(C);

				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update() {

		vector<clsCurrency> _vCurrencies;

		_vCurrencies = _LoadCurrenciesDataFromFile();

		for (clsCurrency& C : _vCurrencies) {

			if (C.GetCurrencyCode() == GetCurrencyCode()) {

				C = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(_vCurrencies);
	}

	static clsCurrency _GetEmptyCurrencyObject() {

		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate) {

		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	static vector<clsCurrency> GetAllUSDRates() {

		return _LoadCurrenciesDataFromFile();
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	string GetCountry() {

		return _Country;
	}

	string GetCurrencyCode() {

		return _CurrencyCode;
	}

	string GetCurrencyName() {

		return _CurrencyName;
	}

	void UpdateRate(float NewRate) {

		_Rate = NewRate;
		_Update();
	}

	float GetRate() {

		return _Rate;
	}

	static clsCurrency FindByCode(string CurrencyCode) {

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream MyFile;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.GetCurrencyCode() == CurrencyCode) {

					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country) {

		Country = clsString::UpperAllString(Country);

		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAllString(Currency.GetCountry()) == Country) {

					MyFile.close();
					return Currency;
				}
			}

			MyFile.close();
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode) {

		clsCurrency C1 = clsCurrency::FindByCode(CurrencyCode);

		return (!C1.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList() {

		return _LoadCurrenciesDataFromFile();
	}

	float ConvertToUSD(float Amount) {

		return (float)(Amount / GetRate());
	}

	float ConvertToOtherCurrency(float Amount, clsCurrency Currency2) {

		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.GetCurrencyCode() == "USD") {

			return AmountInUSD;
		}

		return (float)(AmountInUSD * Currency2.GetRate());
	}
};

