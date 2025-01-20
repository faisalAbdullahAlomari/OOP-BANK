#pragma once
#include <iostream>
#include "clsScreen.h"
#include "iomanip"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:

	static void _PrintTransferLog(clsBankClient::stTransferLogRecord TransferLog) {

		cout << "\t| " << setw(21) << left << TransferLog.DateTime;
		cout << "| " << setw(12) << left << TransferLog.SourceAccountNumber;
		cout << "| " << setw(12) << left << TransferLog.DestinationAccountNumber;
		cout << "| " << setw(9) << left << TransferLog.Amount;
		cout << "| " << setw(12) << left << TransferLog.srcBalanceAfter;
		cout << "| " << setw(12) << left << TransferLog.dstBalanceAfter;
		cout << "| " << setw(7) << left << TransferLog.Username;
	}

public:

	static void ShowTransferLogScreen() {

		vector<clsBankClient::stTransferLogRecord> vTransferLogRecords = clsBankClient::GetTransferLogList();

		_DrawScreenHeader("\t Transfer Log Screen");

		cout << "\n\t___________________________________________________________________________________________________";
		cout << "\n\t| " << setw(21) << left << "Date/Time";
		cout << "| " << setw(12) << left << "Src Account";
		cout << "| " << setw(12) << left << "Dst Account";
		cout << "| " << setw(9) << left << "Amount";
		cout << "| " << setw(12) << left << "Src Balance";
		cout << "| " << setw(12) << left << "Dst Balance";
		cout << "| " << setw(7) << left << "User";
		cout << "\n\t___________________________________________________________________________________________________\n";

		if (vTransferLogRecords.size() == 0) {

			cout << "\t\t\tNo Transfers Available In The System.\n";
		}
		else {

			for (clsBankClient::stTransferLogRecord Record : vTransferLogRecords) {

				_PrintTransferLog(Record);
				cout << endl;
			}
		}

		cout << "\t___________________________________________________________________________________________________\n";

	}
};

