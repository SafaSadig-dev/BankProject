#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"

class clsTransferLogScreen :protected clsScreen
{
private:
	static void _PrintTransferRecord(clsBankClient::stTransferLog Record) {

		cout << setw(8) << "" << "| " << left << setw(23) << Record.DateTime;
		cout << "| " << left << setw(8) << Record.SourceAccountNumber;
		cout << "| " << left << setw(8) << Record.DestinationAccountNumber;
		cout << "| " << left << setw(8) << Record.Amount;
		cout << "| " << left << setw(10) << Record.SourceBalanceAfterTransfer;
		cout << "| " << left << setw(10) << Record.DestinationBalanceAfterTransfer;
		cout << "| " << left << setw(8) << Record.UserName;

	}
public:
	static void ShowTransferLogScreen() {

		vector<clsBankClient::stTransferLog> vTransferLogRecords = clsBankClient::GetTransferRegisterList();
		string Title = ("\t  Transfer Log List Screen");

		string SubTile = "\t  (" + to_string(vTransferLogRecords.size()) + ") Record(s).";
		_DrawSreenHeader(Title, SubTile);


		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n"
			<< endl;

		cout << setw(8) << "" << "| " << left << setw(23) << "Data/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		if (vTransferLogRecords.size() == 0) {
			cout << "\t\t\t\t\tNo Records Available In the System!";
		}
		else{

			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "_________________________________________________\n"
				<< endl;

			for (clsBankClient::stTransferLog& Record : vTransferLogRecords) {
				_PrintTransferRecord(Record);
				cout << endl;
			}


		}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________________\n"
			<< endl;


	}
};

