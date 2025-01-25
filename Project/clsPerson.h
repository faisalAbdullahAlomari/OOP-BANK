#pragma once
#include <iostream>
#include <string>
#include "InterfaceCommunication.h"

using namespace std;

class clsPerson : public InterfaceCommunication {

private:

	string _FirstName;
	string _LastName;
	string _Email;
	string _Phone;

public:

	clsPerson(string FirstName, string LastName, string Email, string Phone) {

		_FirstName = FirstName;
		_LastName = LastName;
		_Email = Email;
		_Phone = Phone;
	}

	void setFirstName(string FirstName) {

		_FirstName = FirstName;
	}

	string getFirstName() {

		return _FirstName;
	}

	__declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	void setLastName(string LastName) {

		_LastName = LastName;
	}

	string getLastName() {

		return _LastName;
	}

	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	void setEmail(string Email) {

		_Email = Email;
	}

	string getEmail() {

		return _Email;
	}

	__declspec(property(get = getEmail, put = setEmail)) string Email;

	void setPhone(string Phone) {

		_Phone = Phone;
	}

	string getPhone() {

		return _Phone;
	}

	__declspec(property(get = getPhone, put = setPhone)) string Phone;

	string FullName()
	{
		return _FirstName + " " + _LastName;
	}

	void SendEmail(string Title, string Body) {
		

	}

	void SendFax(string Title, string Body) {


	}

	void SendSMS(string Title, string Body) {


	}
};