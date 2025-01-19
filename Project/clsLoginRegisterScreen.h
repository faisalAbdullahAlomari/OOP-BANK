#pragma one
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintLoginRegisterRecord(clsUser::stLoginRegisterRecord LGRecord) {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LGRecord.DateTime;
        cout << "| " << setw(20) << left << LGRecord.Username;
        cout << "| " << setw(20) << left << LGRecord.Password;
        cout << "| " << setw(10) << left << LGRecord.Permissions;
    }

public:

	static void ShowLoginRegisterScreen() {

        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister)) {

            return;
        }

		vector<clsUser::stLoginRegisterRecord> vLGRecord = clsUser::GetLoginRegisetList();

		string Subtitle = "(" + to_string(vLGRecord.size());

		_DrawScreenHeader("\tLogin Register List Screen", Subtitle + ") Record(s).");

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLGRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord Record : vLGRecord)
            {

                _PrintLoginRegisterRecord(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};