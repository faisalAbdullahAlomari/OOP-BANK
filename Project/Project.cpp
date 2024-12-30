
#include<iostream>
#include "clsBankClient.h"

using namespace std;

int main() {

	clsBankClient Client = clsBankClient::Find("A101");
	Client.Print();

	system("pause>0");
	return 0;
}