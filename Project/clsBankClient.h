#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {

		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	string getAccountNumber() {

		return _AccountNumber;
	}

	void setPinCode(string PinCode) {

		_PinCode = PinCode;
	}

	string getPinCode() {

		return _PinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	void setAccountBalance(float AccountBalance) {

		_AccountBalance = AccountBalance;
	}

	float getAccountBalance() {

		return _AccountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	void Print() {

		cout << "\nClient Card:";
		cout << "\n_________________________________";
		cout << "\nFirst Name     : " << FirstName;
		cout << "\nLast Name      : " << LastName;
		cout << "\nFull Name      : " << FullName();
		cout << "\nEmail          : " << Email;
		cout << "\nPhone          : " << Phone;
		cout << "\nAccount Number : " << _AccountNumber;
		cout << "\nPin Code       : " << _PinCode;
		cout << "\nAccount Balance: " << _AccountBalance;
		cout << "\n_________________________________";
	}

	static clsBankClient Find(string AccountNumber) {

		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.getAccountNumber() == AccountNumber) {

					MyFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode) {

		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.getAccountNumber() == AccountNumber && Client.PinCode == PinCode) {

					MyFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}
};

