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

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	struct stTransferLogRecord;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#") {

		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {

		string ClientDataInLine = "";

		ClientDataInLine += Client.FirstName + Seperator;
		ClientDataInLine += Client.LastName + Seperator;
		ClientDataInLine += Client.Email + Seperator;
		ClientDataInLine += Client.Phone + Seperator;
		ClientDataInLine += Client.getAccountNumber() + Seperator;
		ClientDataInLine += Client.PinCode + Seperator;
		ClientDataInLine += to_string(Client.AccountBalance);

		return ClientDataInLine;
	}

	static vector<clsBankClient> _LoadClientsDataFromFile() {

		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLineToClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> vClients) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		string Line;

		if (MyFile.is_open()) {

			for (clsBankClient C : vClients) {

				if (C._MarkForDelete == false) {

					Line = _ConvertClientObjectToLine(C);
					MyFile << Line << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update() {

		vector<clsBankClient> _vClients;

		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.getAccountNumber() == getAccountNumber()) {

				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string Line) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << Line << endl;

			MyFile.close();
		}
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	static clsBankClient _GetEmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient, string Username, string Seperator = "#//#") {

		string Line;

		Line += clsDate::GetSystemDateTimeString() + Seperator;
		Line += getAccountNumber() + Seperator;
		Line += DestinationClient.getAccountNumber() + Seperator;
		Line += to_string(Amount) + Seperator;
		Line += to_string(getAccountBalance()) + Seperator;
		Line += to_string(DestinationClient.getAccountBalance()) + Seperator;
		Line += Username;

		return Line;
	}

	static stTransferLogRecord _ConvertTransferLineToRecord(string Line, string Seperator = "#//#") {

		stTransferLogRecord Record;

		vector<string> vTransferLogRecord = clsString::Split(Line, Seperator);

		Record.DateTime = vTransferLogRecord[0];
		Record.SourceAccountNumber = vTransferLogRecord[1];
		Record.DestinationAccountNumber = vTransferLogRecord[2];
		Record.Amount = stof(vTransferLogRecord[3]);
		Record.srcBalanceAfter = stof(vTransferLogRecord[4]);
		Record.dstBalanceAfter = stof(vTransferLogRecord[5]);
		Record.Username = vTransferLogRecord[6];

		return Record;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string Username) {

		string Line = _PrepareTransferLogRecord(Amount, DestinationClient, Username);

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << Line << endl;

			MyFile.close();
		}
	}

public:

	struct stTransferLogRecord {

		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float dstBalanceAfter;
		string Username;
	};

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

	/*
	No UI Related Code Inside Object
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
	}*/

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

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2 };

	enSaveResults Save() {

		switch (_Mode) {

		case enMode::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
			break;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;

		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber)) {
				return enSaveResults::svFailedAccountNumberExists;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
			break;

		}
	}

	static bool IsClientExist(string AccountNumber) {

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	bool Delete() {

		vector<clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.getAccountNumber() == _AccountNumber) {

				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
		*this = _GetEmptyClientObject();

		return true;
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector<clsBankClient> GetClientsList() {

		return _LoadClientsDataFromFile();
	}

	void Deposit(double Amount) {

		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount) {

		if (Amount > _AccountBalance) {

			return false;
		}
		else {

			AccountBalance -= Amount;
			Save();
		}
	}

	static double GetTotalBalances() {

		vector<clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient C : vClients) {

			TotalBalances += C.AccountBalance;

		}

		return TotalBalances;
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient, string Username) {

		if (Amount > AccountBalance) {

			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount, DestinationClient, Username);
		return true;
	}

	static vector<stTransferLogRecord> GetTransferLogList() {

		vector<stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			stTransferLogRecord TransferRecord;

			while (getline(MyFile, Line)) {

				TransferRecord = _ConvertTransferLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);
			}

			MyFile.close();
		}

		return vTransferLogRecord;
	}
};