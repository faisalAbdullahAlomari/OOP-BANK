#pragma once

#include <iostream>
#include "clsDate.h"
#include "clsString.h"

using namespace std;


class clsInputValidate
{
public:

	static bool IsNumberBetween(short Number, short From, short To) {

		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(int Number, int From, int To) {

		return (Number >= From && Number <= To);
	}
	
	static bool IsNumberBetween(double Number, double From, double To) {

		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(float Number, float From, float To) {

		return (Number >= From && Number <= To);
	}

};

