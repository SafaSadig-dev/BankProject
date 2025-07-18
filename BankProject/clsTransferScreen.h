#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsTransferScreen : protected clsScreen
{
private:

	static clsBankClient ReadClient(string msg) {
		string AccountNumber = clsInputValidate::ReadWord(msg);

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadWord("Invalid Account Number , Choose another ? ");
		}

		clsBankClient Clinet = clsBankClient::Find(AccountNumber);

		return Clinet;
	}

	static float _ReadAmount(clsBankClient SourceClient) {
		float Amount = 0;
		cout << "\n\nEnter Transfer Amount ? ";
		Amount = clsInputValidate::ReadFloatNumber();

		// Validate that the amount does not exceeds the balance
		while (Amount > SourceClient.GetAccoutBalance())
		{
			cout << "\nAmount Exceeds the balance, you can withdraw up to : " << SourceClient.GetAccoutBalance() << endl;
			cout << "Please enter another amount? ";
			Amount = clsInputValidate::ReadFloatNumber();
		}

		return Amount;

	}

	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.GetAccoutNumber();
		cout << "\nBalance     : " << Client.GetAccoutBalance();
		cout << "\n___________________\n";
	}

public:
	static void ShowTransferScreen() {
		_DrawSreenHeader("\t  Transfer Screen");

		clsBankClient SourceClient = ReadClient("\nPlease Enter account Number To Transfer From : ");
		_PrintClientCard(SourceClient);


		clsBankClient DestinationClient = ReadClient("\nPlease Enter account Number To Transfer To : ");

		while(DestinationClient.GetAccoutNumber() == SourceClient.GetAccoutNumber() ||
			!clsBankClient::IsClientExist(DestinationClient.GetAccoutNumber())) {
			cout << "\nInvalid Account Number Or You Enter same Account Number!\n";
			DestinationClient = ReadClient("Please Enter account Number To Transfer To : ");
		}

		_PrintClientCard(DestinationClient);

		float Amount = 0;
		Amount = _ReadAmount(SourceClient);

		char Answer = 'n';
		cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient))
			{
				
				cout << "\nTransfer done Successfully.\n\n";

				

			}
			else
			{
				cout << "Error!!\n";
				cout << "Transfer Faild...\n";

			}

			_PrintClientCard(SourceClient);

			_PrintClientCard(DestinationClient);
		}
		else {
			cout << "\nOperation was cancelled.\n";
		}



	}
};

