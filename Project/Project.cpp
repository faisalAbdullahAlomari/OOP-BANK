
#include<iostream>
#include "clsLoginScreen.h"
#include "clsCurrency.h"

using namespace std;

int main() {

	while (true) {
		
		if (!clsLoginScreen::ShowLoginScreen()) {
			break;
		}
	}

	return 0;
}