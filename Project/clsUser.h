#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	enum enMode {
		EmptyMode = 0,
		UpdateMode = 1,
		AddNewMode = 2
	};
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkedForDelete = false;

	struct stLoginRegisterRecord;

	static stLoginRegisterRecord _ConverLoginRegisterLineToRecord(string Line, string Seperator="#//#") {

		stLoginRegisterRecord LoginRegisterRecord;

		vector<string> vLoginRegisterRecordDataLine = clsString::Split(Line, Seperator);

		LoginRegisterRecord.DateTime = vLoginRegisterRecordDataLine[0];
		LoginRegisterRecord.Username = vLoginRegisterRecordDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(vLoginRegisterRecordDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(vLoginRegisterRecordDataLine[3]);

		return LoginRegisterRecord;
	}

	string _PrepareLoginRecord(string Seperator = "#//#") {

		string LoginRecord = "";

		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;
	}

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#") {

		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4],
			clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#") {

		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.getUserName() + Seperator;
		UserRecord += clsUtil::EncryptText(User.getPassword()) + Seperator;
		UserRecord += to_string(User.getPermissions());

		return UserRecord;
	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector<clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLineToUserObject(Line);

				vUsers.push_back(User);
			}

			MyFile.close();
		}

		return vUsers;
	}

	static void _SaveUsersDataToFile(vector<clsUser> vUsers) {

		fstream MyFile;

		MyFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyFile.is_open()) {

			for (clsUser U : vUsers) {

				if (U._MarkedForDelete == false) {

					DataLine = _ConvertUserObjectToLine(U);

					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update() {

		vector<clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers) {

			if (U.getUserName() == getUserName()) {

				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);
	}

	void _AddNew() {

		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string stDataLine) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	struct stLoginRegisterRecord {

		string DateTime;
		string Username;
		string Password;
		int Permissions;
	};

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
	
	string getUserName() {

		return _UserName;
	}

	void setUserName(string UserName) {

		_UserName = UserName;
	}

	__declspec(property(get = getUserName, put = setUserName)) string UserName;

	void setPassword(string Password)
	{
		_Password = Password;
	}

	string getPassword()
	{
		return _Password;
	}

	__declspec(property(get = getPassword, put = setPassword)) string Password;

	void setPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int getPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = getPermissions, put = setPermissions)) int Permissions;

	enum enPermissions {
		pAll = -1,
		pListClients = 1,
		pAddNewClient = 2,
		pDeleteClient = 4,
		pUpdateClient = 8,
		pFindClient = 16,
		pTransactions = 32,
		pManageUsers = 64,
		pLoginRegister = 128
	};

	bool IsEmpty() {

		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete() {

		return _MarkedForDelete;
	}

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();

		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults{
		svFailedEmptyObject = 0,
		svSucceeded = 1,
		svFailedUserExists = 2};

	enSaveResults Save() {

		switch (_Mode) {
		case enMode::EmptyMode:
			if (IsEmpty()){

				return enSaveResults::svFailedEmptyObject;
			}
			break;

		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
			break;

		case enMode::AddNewMode:
			if (clsUser::IsUserExist(_UserName)) {

				return enSaveResults::svFailedUserExists;
			}
			else {

				_AddNew();

				_Mode = enMode::UpdateMode;

				return enSaveResults::svSucceeded;
			}

			break;
		}
	}

	static bool IsUserExist(string UserName) {

		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	bool Delete() {

		vector<clsUser> _vUsers;

		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers) {

			if (U.UserName == _UserName) {

				U._MarkedForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static clsUser GetAddNewUserObject(string UserName) {

		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector<clsUser> GetUsersList() {

		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermission(enPermissions Permission) {

		if (this->Permissions == enPermissions::pAll) {

			return true;
		}

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;
	}

	void RegisterLogin() {

		string DataLine = _PrepareLoginRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static vector<stLoginRegisterRecord> GetLoginRegisetList() {

		stLoginRegisterRecord LoginRegisterRecord;
		vector<stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				LoginRegisterRecord = _ConverLoginRegisterLineToRecord(Line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}

			MyFile.close();
		}

		return vLoginRegisterRecord;
	}
};