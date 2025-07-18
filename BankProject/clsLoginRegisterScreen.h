#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>


class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRecord(clsUser::stLoginRegisterRecord Record) {

		cout << setw(8) << "" << "| " << left << setw(35) << Record.DateTime;
		cout << "| " << left << setw(20) << Record.UserName;
		cout << "| " << left << setw(20) << Record.Password;
		cout << "| " << left << setw(10) << Record.Permissions;

	}

public:
	static void ShowLoginRegisterScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pShowLoginRegister))
		{
			return;// this will exit the function and it will not continue
		}

		string Title = "Login Register List Screen";
		vector<clsUser::stLoginRegisterRecord> vLoginRecords = clsUser::GetLoginRegisterList();

		string SubTile = "\t  (" + to_string(vLoginRecords.size()) + ") Record(s).";
		_DrawSreenHeader(Title, SubTile);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n"
			<< endl;


		cout << setw(8) << "" << "| " << left << setw(35) << "Data/Time";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n"
			<< endl;


		if (vLoginRecords.size() == 0) {
			cout << "\t\t\t\t\tNo Records Available In the System!";
		}
		else {
			

			for (clsUser::stLoginRegisterRecord& Record : vLoginRecords) {
				_PrintLoginRecord(Record);
				cout<<endl;
			}


		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n"
			<< endl;


	}

};

