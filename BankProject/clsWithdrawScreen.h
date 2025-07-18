#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"


class clsWithdrawScreen : protected clsScreen
{
private:
    static void _PrintClientCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FristName();
        cout << "\nLastName    : " << Client.LastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.GetAccoutNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccoutBalance();
        cout << "\n___________________\n";
    }
public:
	static void ShowWithdrawScreen() {
		_DrawSreenHeader("\t   Withdraw Screen");



        string AccountNumber = clsInputValidate::ReadWord("Please Enter Accout Number ? ");

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = clsInputValidate::ReadWord("choose another one: ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        cout << "\nPlease enter withdraw amount? ";
        float Amount = clsInputValidate::ReadFloatNumber();

        // Validate that the amount does not exceeds the balance
        while (Amount > Client.GetAccoutBalance())
        {
            cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.GetAccoutBalance() << endl;
            cout << "Please enter another amount? ";
            Amount = clsInputValidate::ReadFloatNumber();
        }


        char Answer = 'n';

        cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Withdrew Successfully.\n";
                cout << "\nNew Balance Is: " << Client.GetAccoutBalance();
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << Amount;
                cout << "\nYour Balance is: " << Client.GetAccoutBalance();

            }
        }
        else {
            cout << "\nOperation was cancelled.\n";
        }
	}
};

