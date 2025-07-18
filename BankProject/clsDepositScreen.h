#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDepositScreen : protected clsScreen
{
private :
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
	static void ShowDepositScreen() {
		_DrawSreenHeader("\t   Deposit Screen");

      
        string AccountNumber = clsInputValidate::ReadWord("Please Enter Accout Number ? ");

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = clsInputValidate::ReadWord("choose another one: ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClientCard(Client);

        cout << "\nPlease enter deposit amount? ";
        float Amount = clsInputValidate::ReadFloatNumber();

       // Client.Deposit(Amount);
        //clsBankClient::enSaveResults SaveResult = Client.Save();

        char Answer = 'n';

        cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Client.Deposit(Amount);
            cout << "\n\nDone Successfully. New balance is: " << Client.GetAccoutBalance();

        }
        else {
            cout << "\nOperation was cancelled.\n";
        }



	}
};

